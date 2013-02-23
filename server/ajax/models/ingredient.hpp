#ifndef INGREDIENT_HPP
#define INGREDIENT_HPP

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

//------------------------------------------------------------------------------
// Describes an ingredient for a list or order
//------------------------------------------------------------------------------
class Ingredient
{
  public:

    Ingredient(const boost::property_tree::ptree& pt);

    const std::string& getName() const;

    const std::string& getKey() const;

    float getAmount() const;

    void output(std::ostream& s, unsigned indent = 0) const;

  private:

    // The ingredient key
    std::string mKey;

    // The ingredient name
    std::string mName;

    // The ingredient amount in ounces
    float mAmount;
};

#endif // INGREDIENT_HPP
