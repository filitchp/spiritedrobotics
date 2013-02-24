#ifndef ORDER_HPP
#define ORDER_HPP

#include <string>
#include <vector>
#include "models/drink.hpp"

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class Order
{
  public:

    Order(std::string drinkKey, std::string customerName, unsigned timestamp, std::vector<Ingredient> ingredients);

    std::string getDrinkKey() const;

    std::string getCustomerName() const;

    unsigned getTimestamp() const;

    std::string getOrderId() const;

    void output(std::ostream& s, unsigned indent = 0) const;

  private:

    // The unique drink key
    std::string mDrinkKey;

    // The name of the person that ordered it
    std::string mCustomerName;

    // The time it was ordered
    unsigned mTimestamp;

    // The exact ingredients that went into this order
    std::vector<Ingredient> mIngredients;

};

#endif // ORDER_HPP
