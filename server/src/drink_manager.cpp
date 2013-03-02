#include "drink_manager.hpp"

#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include <fcntl.h>    // File control definitions
#include <errno.h>    // Error number definitions
#include <stdio.h>    // Standard input/output definitions
#include <string.h>   // String function definitions

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include <boost/lexical_cast.hpp>

#include "utils/table_printer.hpp"

using namespace boost::filesystem;
using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DrinkManager::DrinkManager(const string& rootPath)
{

  stringstream configFilePath(stringstream::out);
  configFilePath << rootPath << "/assets/json/barbot.json";

  readSystemConfiguration(configFilePath.str());

  stringstream drinksPath(stringstream::out);
  drinksPath << rootPath << "/assets/json/drinks";

  readAllDrinks(drinksPath.str());
  createAvailableDrinkList();

  // DEBUG
  printAllDrinkSummary();

  printAllDrinkIngredients();

  // DEBUG
  //outputDrinkList(cout, 0);

  // Serial port guide: http://www.easysw.com/~mike/serial/serial.html#2_5_2

  string serialDevice = "/dev/ttyUSB0";

  // USB device
  mFd = open(serialDevice.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);

  if (mFd <= 0)
  {
    cerr << "ERROR: could not open " << serialDevice << endl;
  }

  cout << "Opened " << serialDevice << endl;

  // Non-Blocking mode
  fcntl(mFd, F_SETFL, FNDELAY);

  // Get the current options for the port...
  // (and save them so we can write them back on close)
  tcgetattr(mFd, &mOriginalOptions);

  struct termios newOptions;

  // Set serial speed
  // B9600      9600 baud
  // B19200    19200 baud
  // B38400    38400 baud
  // B57600   57,600 baud
  // B76800   76,800 baud
  // B115200 115,200 baud

  if (cfsetispeed(&newOptions, B9600) == -1)
  {
    cerr << "ERROR: Could not set the input speed" << endl;
  }

  if (cfsetospeed(&newOptions, B9600) == -1)
  {
    cerr << "ERROR: Could not set the output speed" << endl;
  }

  //--------------------
  // Control mode flags
  //--------------------

  // Disable hardware flow control
  newOptions.c_cflag &= ~CRTSCTS;

  // No parity (8N1)
  newOptions.c_cflag &= ~PARENB;
  newOptions.c_cflag &= ~CSTOPB;
  newOptions.c_cflag &= ~CSIZE;
  newOptions.c_cflag |= CS8;

  // Enable the receiver and set local mode...
  newOptions.c_cflag |= (CLOCAL | CREAD);

  //------------------
  // Input mode flags
  //------------------

  // Disable software flow control
  newOptions.c_iflag &= ~(IXON | IXOFF | IXANY);

  //-------------------
  // Output mode flags
  //-------------------

  // Raw output
  newOptions.c_oflag &= ~OPOST;

  //------------------
  // Local mode flags
  //------------------

  // Raw mode (disable canonical mode, don't echo, and disable signals)
  newOptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

  // Set the new options for the port...
  if (tcsetattr(mFd, TCSAFLUSH, &newOptions) == -1)
  {
    cerr << "ERROR: Could not set the options for the serial port" << endl;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DrinkManager::~DrinkManager()
{
  if (mFd > 0)
  {
    tcsetattr(mFd, TCSANOW, &mOriginalOptions);

    struct termios options;
    tcgetattr(mFd, &options);

    close(mFd);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::readSystemConfiguration(string systemConfigurationPath)
{
  // Create an empty property tree object
  ptree pt;

  // Parse the system configuration file
  read_json(systemConfigurationPath, pt);

  // Create the system configuration object
  mpBarbot = new BarBot(pt);

  // DEBUG
  mpBarbot->printTowerDebug();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::createAvailableDrinkList()
{
  bool allRumIsTheSame = true;

  BOOST_FOREACH(const Drink& drink, mAllDrinks)
  {

    bool valid = true;

    BOOST_FOREACH(const Ingredient& ing, drink.getIngredients())
    {
      if (!mpBarbot->hasTowerWithIngredient(ing.getKey()))
      {
        valid = false;
        //cout<<"This ingredient Doesn't exist!! "<<ing.getKey()<<" for "<<drink.getName()<<endl;
      }
    }

    if (valid)
    {
      //cout << "This Drink is valid " << drink.getName() << endl;
      mValidDrinks.push_back(drink);
    }
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::readAllDrinks(string pathDrinkDirectory)
{
  path p(pathDrinkDirectory);

  vector<path> drinkPaths;
  try
  {
    // If the path exists and is a directory
    if (exists (p) && is_directory(p))
    {
      // DEBUG
      //cout << p << " is a directory containing:" << endl;
      //copy(directory_iterator(p), directory_iterator(), ostream_iterator<directory_entry>(cout, "\n"));

      // Store all paths in a vector
      copy(directory_iterator(p), directory_iterator(), back_inserter(drinkPaths));
    }
    else
    {
      cout << p << " does not exist\n";
    }
  }
  catch (const filesystem_error& ex)
  {
    cout << ex.what() << endl;
  }

  for (vector<path>::const_iterator it(drinkPaths.begin()); it != drinkPaths.end(); ++it)
  {
    path drinkPath = *it;

    // DEBUG
    //cout << "   " << drinkPath.filename() << '\n';

    ptree dpt;
    read_json(drinkPath.string(), dpt);

    Drink drink(dpt);

    unsigned type = drink.getType();

    if (type == DrinkTypeShot)
    {
      normalizeDrink(drink, 2.5);
    }
    else if (type == DrinkTypeLowBall)
    {
      normalizeDrink(drink, 5);
    }
    else if (type == DrinkTypeHighBall)
    {
      normalizeDrink(drink, 8);
    }

    mAllDrinks.push_back(drink);
  }
}

//------------------------------------------------------------------------------
// This takes the original ingredient amounts and normalizes them to sum to
// the desired total amount.
// normalizedAmount - the new drink size in ounces
//------------------------------------------------------------------------------
void DrinkManager::normalizeDrink(Drink& d, float normalizedAmount)
{
  float totalAmount = 0;

  vector<Ingredient> ingredients = d.getIngredients();

  BOOST_FOREACH(const Ingredient& i, ingredients)
  {
    totalAmount += i.getAmount();
  }

  BOOST_FOREACH(const Ingredient& i, ingredients)
  {
    float percent = i.getAmount()/totalAmount;
    float newAmount = percent*normalizedAmount;

    d.normalizeIngredient(i.getKey(), newAmount);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::printAllDrinkSummary() const
{
  unsigned maxKeyWidth = 0;
  unsigned maxNameWidth = 0;
  unsigned maxImagePathWidth = 0;
  unsigned descriptionWidth = 10;

  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey().size() > maxKeyWidth)
    {
      maxKeyWidth = d.getKey().size();
    }

    if (d.getName().size() > maxNameWidth)
    {
      maxNameWidth = d.getKey().size();
    }

    if (d.getImagePath().size() > maxImagePathWidth)
    {
      maxImagePathWidth = d.getImagePath().size();
    }
  }

  bprinter::TablePrinter tp(&std::cout);

  cout << "maxNameWidth " << maxNameWidth << endl;

  tp.AddColumn("KEY", maxKeyWidth + 2);
  tp.AddColumn("NAME", 38);
  tp.AddColumn("INGR", 4);
  tp.AddColumn("TYPE", 4);
  tp.AddColumn("MAKE", 4);

  tp.PrintHeader();

  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    string canMake = "  ";

    BOOST_FOREACH(const Drink& vd, mValidDrinks)
    {
      if (vd.getKey() == d.getKey())
      {
        canMake = " x ";
        break;
      }
    }

    tp << d.getKey() << d.getName() << d.getIngredients().size() << d.getType() << canMake;
  }

  tp.PrintFooter();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::printAllDrinkIngredients() const
{
  unsigned maxKeyWidth = 0;
  unsigned maxNameWidth = 0;
  unsigned maxImagePathWidth = 0;
  unsigned descriptionWidth = 10;
  unsigned maxIngredientDisplay = 0;
  vector<string> ingredientDisplay;

  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey().size() > maxKeyWidth)
    {
      maxKeyWidth = d.getKey().size();
    }

    if (d.getImagePath().size() > maxImagePathWidth)
    {
      maxImagePathWidth = d.getImagePath().size();
    }

    vector<Ingredient> ingredients = d.getIngredients();

    stringstream ss(stringstream::out);
    ss.precision(2);
    BOOST_FOREACH(const Ingredient i, ingredients)
    {
      ss << i.getKey() << " " << i.getAmount() << "oz ";
    }

    string ingredientString = ss.str();

    //cout << ingredientString << endl;

    if (ingredientString.size() > maxIngredientDisplay)
    {
      maxIngredientDisplay = ingredientString.size();
    }

    ingredientDisplay.push_back(ingredientString);
  }

  bprinter::TablePrinter tp(&std::cout);

  tp.AddColumn("KEY", maxKeyWidth + 1);
  tp.AddColumn("INGREDIENTS", maxIngredientDisplay + 4);
  tp.AddColumn("MAKE", 4);

  tp.PrintHeader();

  unsigned i = 0;
  unsigned makeCount = 0;
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    string canMake = "  ";

    BOOST_FOREACH(const Drink& vd, mValidDrinks)
    {
      if (vd.getKey() == d.getKey())
      {
        canMake = " x ";
        makeCount++;
        break;
      }
    }

    tp << d.getKey() <<  ingredientDisplay[i] << canMake;

    ++i;
  }

  tp.PrintFooter();

  cout << "We can make " << makeCount << " out of " << mAllDrinks.size() << " drinks" << endl;
}

//------------------------------------------------------------------------------
// Determine the number of milliseconds difference between two timeval structs
//------------------------------------------------------------------------------
long millisecondDelta(struct timeval start, struct timeval end)
{
  double seconds, uSeconds;
  seconds  = (double)(end.tv_sec  - start.tv_sec);
  uSeconds = (double)(end.tv_usec - start.tv_usec);

  long delta = (long)(((seconds) * 1000.0 + uSeconds/1000.0) + 0.5);
  return delta;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<unsigned char> DrinkManager::constructTowerMessage(
  unsigned char towerId,
  unsigned char command,
  float amount,
  float flowRate)
{
  vector<unsigned char> message;

  //header byte
  unsigned char headerDataByte = 0x80 | towerId;

  message.push_back(headerDataByte);
  message.push_back(command);

  unsigned char amountDataByte = flowRate * amount;

  // The MSB must be 0 so we max out at 0x7F (127)
  if (amountDataByte > 127)
  {
    amountDataByte = 127;
  }

  message.push_back(amountDataByte);

  // TODO: checksum
  message.push_back(0xC5);

  return message;
}

//------------------------------------------------------------------------------
// For debugging and calibrating each tower
//
// BYTE 1 - Header = 0x80 (header byte for all)
// BYTE 2 - Command type = 0x40 (Pour drink)
// BYTE 3 - Command data = amount x flowRate
// BYTE 4 - Footer + checksum
//------------------------------------------------------------------------------
bool DrinkManager::testTower(unsigned char towerId, float amount)
{

  if (towerId != 0)
  {
    if ((mpBarbot->isTowerIdValid(towerId) == false))
    {
      return false;
    }
  }

  if (mFd <= 0)
  {
    cerr << "ERROR: serial port is not open" << endl;
    return false;
  }

  float flowRate = 0;

  if (towerId != 0)
  {
    Tower tower = mpBarbot->getTowerById(towerId);

    flowRate = tower.getFlowRate();
  }
  else
  {
    cerr << "ERROR: we do not have a tower with that ID" << endl;
    return false;
  }

  if (amount < 0)
  {
    return false;
  }

  static unsigned char POUR_DRINK_COMMAND = 0x40;

  vector<unsigned char> message = constructTowerMessage(
    towerId, POUR_DRINK_COMMAND, amount, flowRate);

  unsigned char msg[4];

  unsigned i = 0;
  BOOST_FOREACH(unsigned char byteToSend, message)
  {
    printf("%2X ", byteToSend);
    cout <<  endl;

    msg[i] = byteToSend;

    ++i;
  }

  ssize_t bytesWritten = write(mFd, msg, 4);

  if (bytesWritten > 0)
  {
    cout << "Wrote " << (unsigned)bytesWritten << " bytes" << endl;

    readData(500);
  }
  else
  {
    cout << "ERROR: Could not write any bytes" << endl;
    return false;
  }

  return true;
}

bool DrinkManager::sendInitMessage()
{

  cout << "Initializing towers..." << endl;
  static unsigned char INIT_ADDRESS = 0x80;
  static unsigned char INIT_COMMAND = 0x02;

  unsigned char msg[4];
  msg[0] = INIT_ADDRESS;
  msg[1] = INIT_COMMAND;
  msg[2] = 0x01;
  msg[3] = 0xC0;

  cout << "Init tower message: " << endl;
  for (int i = 0; i < 4; ++i)
  {
    printf("%d : %2X\n", i, msg[i]);
  }

  ssize_t bytesWritten = write(mFd, msg, 4);

  if (bytesWritten != 4)
  {
    cout << "ERROR: could not send bytes to init tower" << endl;
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
// For debugging and calibrating each tower
//------------------------------------------------------------------------------
bool DrinkManager::initTowers()
{
  if (mFd <= 0)
  {
    cerr << "ERROR: serial port is not open" << endl;
    return false;
  }

  if (!sendInitMessage())
  {
    return false;
  }

  readData(500);

  cout << "=====================" << endl;

  return true;
}

//------------------------------------------------------------------------------
// Get data back from the system
//------------------------------------------------------------------------------
int DrinkManager::readData(long msTimeout)
{

  if (mFd <= 0)
  {
    return 0;
  }

  struct timeval timeStart;
  gettimeofday(&timeStart, NULL);
  unsigned char buffer[255];

  while (1)
  {
    ssize_t bytesRead = read(mFd, buffer, 255);

    if (bytesRead == -1)
    {
      // DEBUG, -1 actually gets returned when there are no bytes available
      //cout << strerror(errno) << endl;
    }
    else if (bytesRead)
    {
      cout << "Got " << bytesRead << " bytes" << endl;
      for (int i = 0; i < bytesRead; ++i)  // for all chars in string
      {
        printf("Got: %X \n", buffer[i]);
      }
    }
    else
    {
      cout << "Got " << bytesRead << " bytes" << endl;
    }

    // Sleep 100 ms
    usleep(100000);

    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);

    long delta = millisecondDelta(timeStart, currentTime);

    if (delta > msTimeout)
    {
      // Time out
      return -2;
    }
  }

  return 1;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::approveOrder(string drinkKey, string customerName, unsigned timestamp)
{
  string orderId = Order::generateOrderId(drinkKey, customerName, timestamp);

  map<string, Order>::iterator it = mPendingOrders.find(orderId);

  // If the order does not exist
  if (it == mPendingOrders.end())
  {
    return false;
  }

  // MAKE THE DRINK HERE!
  Order theOrderToMake = it->second;

  cout << "Order key = " << theOrderToMake.getDrinkKey() << endl;

  vector<Ingredient> ingredients = theOrderToMake.getIngredients();

  BOOST_FOREACH(const Ingredient& i, ingredients)
  {
    Tower t = mpBarbot->getTowerByIngredientKey(i.getKey());

    unsigned towerID = t.getTowerId();
    float flowRate = t.getFlowRate();
    float amount = i.getAmount();

    //testTower(towerID, i.getAmount());

    cout << "  Ingredient key = " << i.getKey() << endl;
    cout << "  Ingredient amt = " << setprecision(3) << i.getAmount() << endl;

    static unsigned char POUR_DRINK_COMMAND = 0x40;

      vector<unsigned char> message = constructTowerMessage(
        towerID, POUR_DRINK_COMMAND, amount, flowRate);

      unsigned char msg[4];

      unsigned j = 0;
      BOOST_FOREACH(unsigned char byteToSend, message)
      {
        printf("  %d : %02X ", j, byteToSend);
        cout <<  endl;

        msg[j] = byteToSend;

        ++j;
      }

      if (mFd > 0)
      {
        ssize_t bytesWritten = write(mFd, msg, 4);

        if (bytesWritten > 0)
        {
          cout << "Wrote " << (unsigned)bytesWritten << " bytes" << endl;

          readData(500);
        }
        else
        {
          cout << "ERROR: Could not write any bytes" << endl;
          return false;
        }

        unsigned amountToSleep = (unsigned) (amount * 1000.0f);

        usleep(amountToSleep);
      }

  }


  //cout<<"***************************************************************"<<endl;
  ofstream drinkRecord;
  const char* file = ("records/"+it->first+".json").c_str();
  drinkRecord.open(file);
  it->second.output(drinkRecord,0);
  drinkRecord.close();

  mApprovedOrders.insert(pair<string, Order>(it->first, it->second));

  mPendingOrders.erase(it);

  return true;

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::addOrder(string drinkKey, string customerName, unsigned timestamp)
{

  vector<Ingredient> ingredients;
  vector<unsigned> towerMessage;

  // Grab the ingredients from the drink key provided
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey() == drinkKey)
    {
      ingredients = d.getIngredients();
      break;
    }
  }

  // If there are no ingredients for this preset (or the preset does not exist)
  if (ingredients.size() == 0)
  {
    return false;
  }

  // use to generate the tower message
    //according to the protocol documnted here: https://github.com/filitchp/spiritedrobotics/wiki/Node-Communication-Protocol
//  unsigned chksum = 0; //xor of all nibbles,
//  BOOST_FOREACH(const Ingredient& ing, ingredients)
//  {
//    //is there a more direct way to do this?
//    unsigned towerID = (mpBarbot->getTowerByIngredientKey(ing.getKey())).getTowerId();
//
//    //header byte
//    unsigned tByte = (towerID << 2) | (0x01);
//    chksum ^= (tByte & 0x0F) ^ (tByte >> 4); // because xor is distributive and associative, it should be fine to do it this way.
//    towerMessage.push_back(tByte);
//
//    //protocol incomplete? to be completed following discussion with paul/ryan
//
//    //footer byte
//    tByte = (0x03)|(chksum & 0x0F);//just in case
//    towerMessage.push_back(tByte);
//
//  }

  Order newOrder(drinkKey, customerName, timestamp, ingredients, towerMessage);

  string orderId = newOrder.getOrderId();

  // If the order ID is unique
  if (mPendingOrders.find(orderId) == mPendingOrders.end())
  {
    // Add the order
    mPendingOrders.insert(std::pair<string, Order>(orderId, newOrder));
  }
  else
  {
    // The order already exists
    // This could happen if the same order gets submitted back-to-back
    // Drunk proof design!!!
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputPendingOrders(std::ostream& s, unsigned indent)
{
  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;

  typedef std::map<std::string, Order> order_map;

  BOOST_FOREACH(const order_map::value_type& orderPair, mPendingOrders)
  {
    Order o = orderPair.second;

    o.output(s, indent + 4);

    count++;

    if (count != mPendingOrders.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputApprovedOrders(std::ostream& s, unsigned indent)
{
  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;

  typedef std::map<std::string, Order> order_map;

  BOOST_FOREACH(const order_map::value_type& orderPair, mApprovedOrders)
  {
    Order o = orderPair.second;

    o.output(s, indent + 4);

    count++;

    if (count != mApprovedOrders.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::getIngredientsForDrinkKey(string key, vector<Ingredient>& ingredients)
{
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey() == key)
    {
      ingredients = d.getIngredients();
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputDrinkList(ostream& s, unsigned indent)
{

  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;
  BOOST_FOREACH(const Drink& d, mValidDrinks)
  {
    d.output(s, indent + 4);

    count++;
    if (count != mValidDrinks.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;

}


