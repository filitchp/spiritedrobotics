#include "models/order.hpp"

#include <iostream>
#include <string>


#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>

using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Order::Order(
  std::string drinkKey,
  std::string customerName,
  unsigned timestamp,
  std::vector<Ingredient> ingredients) :
    mDrinkKey(drinkKey),
    mCustomerName(customerName),
    mTimestamp(timestamp),
    mIngredients(ingredients)
{
}

//------------------------------------------------------------------------------
// Unfortunately writing JSON from property trees has some limitations so
// for now we output it manually.  At least this is fast....
//------------------------------------------------------------------------------
void Order::output(ostream& s, unsigned indent) const
{
  string p = string(indent, ' ');

  s << p << "{" << endl;
  s << p << "  \"key\" : \""      << mDrinkKey     << "\"," << endl;
  s << p << "  \"customer\" : \"" << mCustomerName << "\"," << endl;
  s << p << "  \"date\" : "       << mTimestamp  << ","  << endl;
  s << p << "  \"ingredients\" : "  << endl;
  s << p << "  ["  << endl;

  unsigned count = 0;
  BOOST_FOREACH(const Ingredient& i, mIngredients)
  {
    i.output(s, indent + 4);

    count++;
    if (count != mIngredients.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }
  s << p << "  ]" << endl;
  s << p << "}";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Order::getCustomerName() const
{
  return mCustomerName;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Order::getDrinkKey() const
{
  return mDrinkKey;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned Order::getTimestamp() const
{
  return mTimestamp;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
string Order::getOrderId() const
{
  return generateOrderId(mDrinkKey, mCustomerName, mTimestamp);

}

