#include "drink_manager.hpp"

#include <iostream>
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
  tcgetattr(mFd, &mOriginalOptions);

  printf("Input mode flags   = %X\n", mOriginalOptions.c_iflag);
  printf("output mode flags  = %X\n", mOriginalOptions.c_oflag);
  printf("control mode flags = %X\n", mOriginalOptions.c_cflag);
  printf("local mode flags   = %X\n", mOriginalOptions.c_lflag);

  struct termios newOptions;

  // Set serial speed
  // B9600      9600 baud
  // B19200    19200 baud
  // B38400    38400 baud
  // B57600   57,600 baud
  // B76800   76,800 baud
  // B115200 115,200 baud
  cfsetispeed(&newOptions, B115200);
  cfsetospeed(&newOptions, B115200);

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
  tcsetattr(mFd, TCSANOW, &newOptions);

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

    printf("Input mode flags   = %X\n", options.c_iflag);
    printf("output mode flags  = %X\n", options.c_oflag);
    printf("control mode flags = %X\n", options.c_cflag);
    printf("local mode flags   = %X\n", options.c_lflag);

    while(close(mFd) != 0);

    cout << "Closed mFd" << endl;
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

    cout << "   " << drinkPath.filename() << '\n';

    ptree dpt;
    read_json(drinkPath.string(), dpt);

    Drink drink(dpt);

    mAllDrinks.push_back(drink);
  }
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
    flowRate = 100;
  }

  // Header byte = 0x80 - header byte for all
  // Command type = 0x40 - Pour drink
  // Command data = 0x01 (amount)
  // Footer + checksum = 0xC5 (random crap)

  if (amount < 0)
  {
    return false;
  }

  static unsigned char POUR_DRINK_COMMAND = 0x40;

  vector<unsigned char> towerMessage;

  //header byte
  unsigned char headerDataByte = 0x80 | towerId;

  towerMessage.push_back(headerDataByte);
  towerMessage.push_back(POUR_DRINK_COMMAND);

  unsigned char amountDataByte = (flowRate*amount)/100.0f;

  // The MSB must be 0 so we max out at 0x7F (127)
  if (amountDataByte > 127)
  {
    amountDataByte = 127;
  }

  towerMessage.push_back(amountDataByte);
  towerMessage.push_back(0xC5);

  unsigned char msg[4];

  unsigned i = 0;
  BOOST_FOREACH(unsigned char byteToSend, towerMessage)
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

    readData(2000);
  }
  else
  {
    cout << "ERROR: Could not write any bytes" << endl;
  }

  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int DrinkManager::readData(long msTimeout)
{
  struct timeval timeStart;
  gettimeofday(&timeStart, NULL);
  unsigned char buffer[255];

  while (1)
  {

    ssize_t bytesRead = read(mFd, buffer, 255);

    
    if (bytesRead == -1){
      cout << strerror(errno) << endl;
    }else if (bytesRead){
      cout << "Got " << bytesRead << " bytes" << endl;
      for (int i = 0; i < bytesRead; ++i)  // for all chars in string
      {
        printf("Got: %X \n", buffer[i]);
      }
    }else{
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
  unsigned chksum = 0; //xor of all nibbles,
  BOOST_FOREACH(const Ingredient& ing, ingredients)
  {
    //is there a more direct way to do this?
    unsigned towerID = (mpBarbot->getTowerByIngredientKey(ing.getKey())).getTowerId();
    //header byte
    unsigned tByte = (towerID << 2) | (0x01);
    chksum ^= (tByte & 0x0F) ^ (tByte >> 4); // because xor is distributive and associative, it should be fine to do it this way.
    towerMessage.push_back(tByte);

      //protocol incomplete? to be completed following discussion with paul/ryan

    //footer byte
    tByte = (0x03)|(chksum & 0x0F);//just in case
    towerMessage.push_back(tByte);

  }

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
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    d.output(s, indent + 4);

    count++;
    if (count != mAllDrinks.size())
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


