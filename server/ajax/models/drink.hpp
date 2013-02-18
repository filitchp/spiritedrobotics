#ifndef DRINK_HPP
#define DRINK_HPP

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "models/ingredient.hpp"

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class Drink
{
  public:

    Drink(const boost::property_tree::ptree& pt);

    const std::string& getKey() const;

    const std::string& getName() const;

    const std::vector<Ingredient>& getIngredients() const;

    const std::string& getDescription() const;

    const std::string& getImagePath() const;

  private:

    void addIngredient(Ingredient& ingredient);

    // The unique drink key
    std::string mKey;

    // The drink name
    std::string mName;

    // Drink description
    std::string mDescription;

    // Drink image path
    std::string mImagePath;

    // The ingredient in the drink
    std::vector<Ingredient> mIngredients;
};

#endif // DRINK_HPP
