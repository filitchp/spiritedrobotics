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

#define COM_LIGHT_MODE_PASSIVE 0x05
#define COM_LIGHT_MODE_FIRE 0x06

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DrinkManager::DrinkManager(const string& rootPath, boost::asio::io_service& io) :
  mRootPath(rootPath),
  mBusy(true),
  mCurrentIngredientIndex(0),
  mTimer(io),
  mIngredientOffsetTimeMs(2000)
{

  stringstream configFilePath(stringstream::out);
  configFilePath << rootPath << "/assets/json/barbot.json";

  readSystemConfiguration(configFilePath.str());

  stringstream drinksPath(stringstream::out);
  drinksPath << rootPath << "/assets/json/drinks";

  readAllDrinks(drinksPath.str());
  createAvailableDrinkList();

  stringstream logsPathSS(stringstream::out);
  logsPathSS << rootPath << "/logs";

  stringstream ordersPathSS(stringstream::out);
  ordersPathSS << logsPathSS.str() << "/orders";

  stringstream debugPathSS(stringstream::out);
  debugPathSS << logsPathSS.str() << "/debug";

  path logsPath(logsPathSS.str());
  path ordersPath(ordersPathSS.str());
  path debugPath(debugPathSS.str());

  try
  {
    // Have to create directories one level at a time...
    if (!exists(logsPath))
    {
      create_directory(logsPath);
    }

    if (!exists(ordersPath))
    {
      create_directory(ordersPath);
    }

    if (!exists(debugPath))
    {
      create_directory(debugPath);
    }
  }
  catch (const filesystem_error& ex)
  {
    cout << ex.what() << endl;
  }

  // Get current time
  struct timeval currentTime;

  gettimeofday(&currentTime, NULL);

  //--------------------------------------------
  // DEBUG configuration (print to console)
  //--------------------------------------------
  mpBarbot->printTowerDebug(cout);

  //--------------------------------------------
  // DEBUG configuration (write to file)
  //--------------------------------------------
  ofstream configLog;
  stringstream configLogSS(stringstream::out);

  configLogSS << debugPathSS.str() << "/" << (unsigned) currentTime.tv_sec
      << "SystemConfig.txt";

  configLog.open(configLogSS.str().c_str());
  mpBarbot->printTowerDebug(configLog);
  configLog.close();

  //--------------------------------------------
  // DEBUG all drink summary (print to console)
  //--------------------------------------------
  printAllDrinkSummary(cout);

  //--------------------------------------------
  // DEBUG all drink summary (write to file)
  //--------------------------------------------
  ofstream allSummaryLog;
  stringstream allDrinkSummarySS(stringstream::out);

  allDrinkSummarySS << debugPathSS.str() << "/" << (unsigned) currentTime.tv_sec
      << "AllDrinkSummary.txt";

  allSummaryLog.open(allDrinkSummarySS.str().c_str());
  printAllDrinkSummary(allSummaryLog);
  allSummaryLog.close();

  //------------------------------------------------
  // DEBUG all drink ingredients (print to console)
  //------------------------------------------------
  printAllDrinkIngredients(cout);

  //--------------------------------------------
  // DEBUG all drink ingredients (write to file)
  //--------------------------------------------

  stringstream allDrinkIngredientsSS(stringstream::out);

  allDrinkIngredientsSS << debugPathSS.str() << "/" << (unsigned) currentTime.tv_sec
      << "AllDrinkIngredients.txt";

  ofstream allIngredientsLog;
  allIngredientsLog.open(allDrinkIngredientsSS.str().c_str());
  printAllDrinkIngredients(allIngredientsLog);
  allIngredientsLog.close();

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
  else
  {

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

    if (cfsetispeed(&newOptions, B38400) == -1)
    {
      cerr << "ERROR: Could not set the input speed" << endl;
    }

    if (cfsetospeed(&newOptions, B38400) == -1)
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

  // The system has initialized so we're no longer busy
  mBusy = false;

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

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::createAvailableDrinkList()
{
  bool allRumIsTheSame = true;

  BOOST_FOREACH(const Drink& drink, mAllDrinks)
  {

    bool valid = false;
    
    //TODO remove this and put it with a generic route -Andrew
    BOOST_FOREACH(const std::string category, drink.getCategories())
    {
       if ((category == "SPACE") || (category == "COCKTAILS"))
       {
         valid = true;
       }
    }

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
      normalizeDrink(drink, 3);
    }
    else if (type == DrinkTypeLowBall)
    {
      normalizeDrink(drink, 5);
    }
    else if (type == DrinkTypeHighBall)
    {
      normalizeDrink(drink, 7);
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
void DrinkManager::printAllDrinkSummary(ostream& os) const
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

  bprinter::TablePrinter tp(&os);

  //cout << "maxNameWidth " << maxNameWidth << endl;

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
void DrinkManager::printAllDrinkIngredients(ostream& os) const
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

  bprinter::TablePrinter tp(&os);

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

  // DEBUG
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

  unsigned int amountDataByte = flowRate * amount;

  // The MSB must be 0 so we max out at 0x7F (127)
  if (amountDataByte > 1<<15)
  {
    amountDataByte = (1<<15) -1;
  }

  unsigned char lowerByte = (char) (amountDataByte & 0x7F);
  unsigned char upperByte = (char) ((amountDataByte>>7) & 0x7F);

  message.push_back(upperByte);
  message.push_back(lowerByte);

  // TODO: checksum
  message.push_back(0xC5);

  return message;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::setTowerReverseTime(unsigned char towerId, float amount)
{

  // Check if the tower is valid (0 is valid because it's the broadcast id)
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

  static unsigned char COMMAND = 0x42;

  vector<unsigned char> message = constructTowerMessage(
    towerId, COMMAND, amount, flowRate);

  unsigned char msg[5];

  unsigned i = 0;
  BOOST_FOREACH(unsigned char byteToSend, message)
  {
    printf("%2X ", byteToSend);
    cout <<  endl;

    msg[i] = byteToSend;

    ++i;
  }

  size_t bytesWritten = write(mFd, msg, 5);

  if (bytesWritten > 0)
  {
    cout << "Wrote " << (unsigned)bytesWritten << " bytes" << endl;
    comReadData(200);
  }
  else
  {
    cout << "ERROR: Could not write any bytes" << endl;
    return false;
  }

  return true;
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

  // Check if the tower is valid (0 is valid because it's the broadcast id)
  if (towerId != 0)
  {
    if ((mpBarbot->isTowerIdValid(towerId) == false))
    {
      return false;
    }
  }

  if (mBusy)
  {
    return false;
  }

  if (mFd > 0)
  {
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

    unsigned char msg[5];

    unsigned i = 0;
    BOOST_FOREACH(unsigned char byteToSend, message)
    {
      printf("%2X ", byteToSend);
      cout <<  endl;

      msg[i] = byteToSend;

      ++i;
    }

    size_t bytesWritten = write(mFd, msg, 5);

    if (bytesWritten > 0)
    {
      cout << "Wrote " << (unsigned)bytesWritten << " bytes" << endl;
      comReadData(200);
    }
    else
    {
      cout << "ERROR: Could not write any bytes" << endl;
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::sendFireLightsMessage()
{

  cout << "Fire lights..." << endl;

  if (mBusy)
  {
    return false;
  }

  return comSetLightsMode((unsigned char)COM_LIGHT_MODE_FIRE);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::sendPassiveLightsMessage()
{

  cout << "Passive lights..." << endl;

  if (mBusy)
  {
    return false;
  }

  return comSetLightsMode((unsigned char)COM_LIGHT_MODE_PASSIVE);
}

//------------------------------------------------------------------------------
// Initializes the system
//------------------------------------------------------------------------------
bool DrinkManager::initTowers()
{
  cout << "=====================" << endl;
  cout << "      initTowers     " << endl;
  cout << "=====================" << endl;

  if (mBusy)
  {
    return false;
  }

  if (!comInitMessage())
  {
    return false;
  }

  comReadData(200);

  cout << "=====================" << endl;

  return true;
}

//------------------------------------------------------------------------------
// Initializes the system
//------------------------------------------------------------------------------
bool DrinkManager::haltTowers()
{

  cout << "=====================" << endl;
  cout << "      haltTowers     " << endl;
  cout << "=====================" << endl;

  if (mFd > 0)
  {
    if (!comHaltMessage())
    {
      return false;
    }

    // See if the system has any data for us
    comReadData(200);
  }

  // Cancel the timer
  mTimer.cancel();

  // Window down immediately
  timerOperationWindDown();

  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::comInitMessage()
{

  if (mFd > 0)
  {
    static unsigned char COMMAND_HEADER = 0x80;
    static unsigned char REASSIGN_ADDRESS_COMMAND = 0x02;

    unsigned char msg[4];
    msg[0] = COMMAND_HEADER;
    msg[1] = REASSIGN_ADDRESS_COMMAND;
    msg[2] = 0x01;
    msg[3] = 0xC0; // TODO: compute checksum

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
  }

  return true;
}

//------------------------------------------------------------------------------
// This is a low-level private method that is not concerned if there is
// anything currently executed
//------------------------------------------------------------------------------
bool DrinkManager::comSetLightsMode(unsigned char mode)
{
  if (mFd > 0)
  {

    // TODO: is it necessary to lock communication to serial or are we ok since
    //       this entire process runs on a single thread?

    static unsigned char COMMAND_HEADER = 0x80;
    static unsigned char SET_LIGHT_COMMAND = 0x45;

    unsigned char msg[4];
    msg[0] = COMMAND_HEADER;
    msg[1] = SET_LIGHT_COMMAND;
    msg[2] = mode;
    msg[3] = 0xC5; // TODO: compute checksum

    cout << "Passive lights message: " << endl;
    for (int i = 0; i < 4; ++i)
    {
      printf("%d : %2X\n", i, msg[i]);
    }

    ssize_t bytesWritten = write(mFd, msg, 4);

    if (bytesWritten != 4)
    {
      cout << "ERROR: could not set lights mode" << endl;
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------
// Here we don't care if the system is busy or not, make it HALT NOW!
//------------------------------------------------------------------------------
bool DrinkManager::comHaltMessage()
{
  if (mFd > 0)
  {
    static unsigned char COMMAND_HEADER = 0x80;
    static unsigned char FORCE_HALT_COMMAND = 0x01;

    unsigned char msg[3];
    msg[0] = COMMAND_HEADER;
    msg[1] = FORCE_HALT_COMMAND;
    msg[2] = 0xC0; // TODO: compute checksum

    for (int i = 0; i < 3; ++i)
    {
      printf("%d : %2X\n", i, msg[i]);
    }

    ssize_t bytesWritten = write(mFd, msg, 3);

    if (bytesWritten != 3)
    {
      cout << "ERROR: could not send bytes to halt tower" << endl;
      return false;
    }
  }

  return true;
}

//------------------------------------------------------------------------------
// Get data back from the system
//------------------------------------------------------------------------------
int DrinkManager::comReadData(long msTimeout)
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
// WARNING: only use this with mTimer and make sure the busy flag is set
// before executing this method
//------------------------------------------------------------------------------
void DrinkManager::timerOperationIngredient()
{

  // Just in case: make sure the current ingredient is set
  if (mCurrentIngredientIndex >= mCurrentIngredients.size())
  {
    // Internal error... wind down the system immediately
    timerOperationWindDown();
    return;
  }

  Ingredient i = mCurrentIngredients[mCurrentIngredientIndex];

  Tower t = mpBarbot->getTowerByIngredientKey(i.getKey());

  unsigned towerID = t.getTowerId();
  float flowRate = t.getFlowRate();
  float amount = i.getAmount();

  cout << "  Ingredient key = " << i.getKey() << endl;
  cout << "  Ingredient amt = " << setprecision(3) << i.getAmount() << endl;

  static unsigned char POUR_DRINK_COMMAND = 0x40;

  vector<unsigned char> message = constructTowerMessage(
    towerID,
    POUR_DRINK_COMMAND,
    amount,
    flowRate);

  unsigned char msg[5];

  unsigned j = 0;
  BOOST_FOREACH(unsigned char byteToSend, message)
  {
    printf("  %d : %02X ", j, byteToSend);
    cout << endl;

    msg[j] = byteToSend;

    ++j;
  }

  if (mFd > 0)
  {
    size_t bytesWritten = write(mFd, msg, 5);

    if (bytesWritten > 0)
    {
      cout << "Wrote " << (unsigned) bytesWritten << " bytes" << endl;

      comReadData(200);
    }
    else
    {
      cout << "ERROR: Could not write any bytes" << endl;
    }
  }

  mCurrentIngredientIndex++;

  // Do we have more ingredients?
  if (mCurrentIngredientIndex == mCurrentIngredients.size())
  {
    // No more ingredients, wind down after the last delay
    mTimer.expires_at(mTimer.expires_at() + boost::posix_time::milliseconds(mLastIngredientWaitMs));
    cout << "Waiting for " << mLastIngredientWaitMs << " ms" << endl;
    mTimer.async_wait(boost::bind(&DrinkManager::timerOperationWindDown, this));
  }
  else
  {
    // Fire up the next ingredient after the delay
    mTimer.expires_at(mTimer.expires_at() + boost::posix_time::milliseconds(mIngredientOffsetTimeMs));
    cout << "Waiting for " << mIngredientOffsetTimeMs << " ms" << endl;
    mTimer.async_wait(boost::bind(&DrinkManager::timerOperationIngredient, this));
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::timerOperationWindDown()
{
  comSetLightsMode((unsigned char)COM_LIGHT_MODE_PASSIVE);

  // We're done, clean-up
  mBusy = false;
  mCurrentIngredientIndex = 0;
  mCurrentIngredients.clear();
}

//------------------------------------------------------------------------------
// Return status
//  1 - Success
//  0 - Order does not exist
// -1 - System is busy
//------------------------------------------------------------------------------
int DrinkManager::approveOrder(string drinkKey, string customerName, unsigned timestamp)
{
  string orderId = Order::generateOrderId(drinkKey, customerName, timestamp);

  // Cannot make the drink, the system is busy
  if (mBusy)
  {
    cout << "ERROR: The system is currently busy making a drink" << endl;
    return -1;
  }

  map<string, Order>::iterator it = mPendingOrders.find(orderId);

  // If the order does not exist
  if (it == mPendingOrders.end())
  {
    cout << "ERROR: The order is not part of the pending orders" << endl;
    return 0;
  }

  //---------------------------------------------------
  // The drink making process officially starts here!
  //---------------------------------------------------
  // Lock out external interaction with the nodes
  mBusy = true;

  Order theOrderToMake = it->second;

  cout << "Started making " << theOrderToMake.getDrinkKey() << endl;

  mCurrentIngredients = theOrderToMake.getIngredients();
  mCurrentIngredientIndex = 0;

  int lastEndTimeIndex = 0;
  int index = 0;
  float lastEndTimeMs = 0;

  static const float estimatedTimeAmoutRatio = 4000.0f;

  // Figure out which ingredient will stop pouring last
  BOOST_FOREACH(const Ingredient& i, mCurrentIngredients)
  {

    float endTimeMs = (float)(index*mIngredientOffsetTimeMs) + i.getAmount()*estimatedTimeAmoutRatio;

    if (endTimeMs >= lastEndTimeMs)
    {
      lastEndTimeMs = endTimeMs;
      lastEndTimeIndex = index;
    }

    // DEBUG
    //cout << i.getName() << "(" << i.getAmount() << " oz) " << endTimeMs << " ms"  << endl;

    ++index;
  }

  mLastIngredientWaitMs = lastEndTimeMs - (mCurrentIngredients.size()-1)*mIngredientOffsetTimeMs;

  //cout << "mLastIngredientWaitMs = " << mLastIngredientWaitMs << " ms" << endl;

  //---------------
  // Log the drink
  //---------------
  ofstream drinkRecord;

  stringstream orderPathSS(stringstream::out);
  orderPathSS << mRootPath << "/logs/orders/" << it->first;

  if (mFd <= 0)
  {
    // If we never successfully opened the serial port we'll assume this is just a debug log
    // so put the term 'debug' into the filename
    orderPathSS << ".debug";
  }

  orderPathSS << ".json";

  drinkRecord.open(orderPathSS.str().c_str());

  it->second.output(drinkRecord, 0);

  drinkRecord.close();

  mApprovedOrders.insert(pair<string, Order>(it->first, it->second));

  mPendingOrders.erase(it);

  // Make the lights look pretty to build suspense
  comSetLightsMode((unsigned char)COM_LIGHT_MODE_FIRE);

  // Start the timer
  mTimer.expires_from_now(boost::posix_time::milliseconds(2800));

  mTimer.async_wait(boost::bind(&DrinkManager::timerOperationIngredient, this));

  return 1;

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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputSystemStatus(ostream& s, unsigned indent)
{

  string p = string(indent, ' ');

  s << p << "{" << endl;
  s << p << "  \"status\" : ";
  if (mBusy)
  {
   s << "\"Busy\"" << endl;
  }
  else
  {
    s << "\"Idle\"" << endl;
  }

  s << p << "}" << endl;
}

