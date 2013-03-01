#ifndef DRINK_MANAGER_HPP
#define DRINK_MANAGER_HPP

#include <string>
#include <vector>
#include <map>
#include <termios.h>  // POSIX terminal control definitions

#include "models/barbot.hpp"
#include "models/drink.hpp"
#include "models/order.hpp"


//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class DrinkManager
{
  public:

    DrinkManager(const std::string& rootPath);
    ~DrinkManager();

    void outputDrinkList(std::ostream& s, unsigned indent);

    void outputPendingOrders(std::ostream& s, unsigned indent);
    void outputApprovedOrders(std::ostream& s, unsigned indent);

    bool getIngredientsForDrinkKey(std::string key, std::vector<Ingredient>& ingredients);

    bool addOrder(std::string drinkKey, std::string customerName, unsigned timestamp);
    bool approveOrder(std::string drinkKey, std::string customerName, unsigned timestamp);
    bool testTower(unsigned char towerId, float amount);

    int readData(long msTimeout);
    void printAllDrinks() const;

  private:

    // Serial port file descriptor
    int mFd;
    struct termios mOriginalOptions;

    // System configuration
    BarBot* mpBarbot;

    // All of the drinks from the drink library
    std::vector<Drink> mAllDrinks;

    // Drinks that can actually be made given the ingredients
    std::vector<Drink> mValidDrinks;

    std::map<std::string, Order> mPendingOrders;
    std::map<std::string, Order> mApprovedOrders;
    std::map<std::string, Order> mRejectedOrders;

    void readSystemConfiguration(std::string systemConfigurationPath);
    void readAllDrinks(std::string systemConfigurationPath);
    void createAvailableDrinkList();

    std::vector<unsigned char> constructTowerMessage(
          unsigned char towerId,
          unsigned char command,
          float amount,
          float flowRate);

};

#endif // DRINK_MANAGER_HPP
