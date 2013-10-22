#ifndef DRINK_MANAGER_HPP
#define DRINK_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <termios.h>  // POSIX terminal control definitions

#include "models/barbot.hpp"
#include "models/drink.hpp"
#include "models/order.hpp"
#include "models/image.hpp"


#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class DrinkManager
{
  public:

    DrinkManager(const std::string& rootPath, boost::asio::io_service& io, bool demoMode);
    ~DrinkManager();

    void outputDrinkList(std::ostream& s, unsigned indent);
    void outputSystemStatus(std::ostream& s, unsigned indent);

    void outputPendingOrders(std::ostream& s, unsigned indent);
    void outputApprovedOrders(std::ostream& s, unsigned indent);

    bool getIngredientsForDrinkKey(std::string key, std::vector<Ingredient>& ingredients);

    bool addOrder(std::string drinkKey, std::string customerName, unsigned timestamp);
    int approveOrder(std::string drinkKey, std::string customerName, unsigned timestamp);
    bool testTower(unsigned char towerId, float amount);
    bool setTowerReverseTime(unsigned char towerId, float amount);

    void normalizeDrink(Drink& d, float normalizedAmount);
    void printAllDrinkIngredients(std::ostream& os) const;

    int comReadData(long msTimeout);
    void printAllDrinkSummary(std::ostream& os) const;

    bool initTowers();
    bool haltTowers();
    bool comInitMessage();
    bool comHaltMessage();
    bool sendFireLightsMessage();
    bool sendPassiveLightsMessage();

    // Callback that starts pouring an ingredient after a timer has elapsed
    void timerOperationIngredient();

    // Callback that gets run after all ingredients have been poured
    void timerOperationWindDown();

  private:

    // Serial port file descriptor
    int mFd;
    struct termios mOriginalOptions;

    bool mDemoMode;

    // Determines if the system is currently busy (making a drink or performing a light show)
    bool mBusy;

    // The current set of ingredients being served (when the system is busy making a drink these ingredients are used)
    std::vector<Ingredient> mCurrentIngredients;
    int mCurrentIngredientIndex;

    // The number of milliseconds to wait to start the next pump
    const int mIngredientOffsetTimeMs;
    int mLastIngredientWaitMs;

    boost::asio::deadline_timer mTimer;

    // The working path (all input/output files are relative to this path)
    std::string mRootPath;

    // System configuration
    BarBot* mpBarbot;

    // All of the drinks from the drink library
    std::vector<Drink> mAllDrinks;

    // Drinks that can actually be made given the ingredients
    std::vector<Drink> mValidDrinks;

    std::map<std::string, Order> mPendingOrders;
    std::map<std::string, Order> mApprovedOrders;
    std::map<std::string, Order> mRejectedOrders;

    std::map<std::string, Image> mImages;

    void readSystemConfiguration(std::string systemConfigurationPath);
    void readImageAttribution(std::string imageAttributionPath);

    void readAllDrinks(std::string systemConfigurationPath);
    void createAvailableDrinkList();

    std::vector<unsigned char> constructTowerMessage(
          unsigned char towerId,
          unsigned char command,
          float amount,
          float flowRate);

    bool comSetLightsMode(unsigned char mode);

};

#endif // DRINK_MANAGER_HPP
