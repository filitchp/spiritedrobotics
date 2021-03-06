#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>
#include <ostream>
#include <sstream>

#include "models/drink.hpp"

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class Order
{
  public:

    static std::string generateOrderId(
      const std::string& drinkKey,
      const std::string& customerName,
      unsigned timestamp)
    {
      std::stringstream oss(std::stringstream::out);
      oss << timestamp << drinkKey << customerName;

      return oss.str();
    }

    Order(
      std::string drinkKey,
      std::string customerName,
      unsigned timestamp,
      std::vector<Ingredient> ingredients,
      std::vector<unsigned int> towerMessage);

    std::string getDrinkKey() const;

    std::string getCustomerName() const;

    unsigned getTimestamp() const;

    std::string getOrderId() const;

    std::vector<Ingredient> getIngredients();

    std::vector<unsigned int> getTowerMessage();

    void output(std::ostream& s, unsigned indent = 0) const;

  private:

    // The unique drink key
    std::string mDrinkKey;

    // The name of the person that ordered it
    std::string mCustomerName;

    //the hexdata to be sent to the tower boards
    std::vector<unsigned int> mTowerMessage;

    // The time it was ordered
    unsigned mTimestamp;

    // The exact ingredients that went into this order
    std::vector<Ingredient> mIngredients;

};

#endif // ORDER_HPP
