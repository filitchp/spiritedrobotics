#ifndef DRINK_HPP
#define DRINK_HPP

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "models/ingredient.hpp"

enum
{
  DrinkTypeShot = 0,
  DrinkTypeLowBall = 1,
  DrinkTypeHighBall = 2,
  DrinkTypeClassics = 3,
  DrinkTypeCocktails = 4
};

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class Drink
{
  public:

    Drink(const boost::property_tree::ptree& pt);

    const std::string& getKey() const;

    const std::string& getName() const;

    std::vector<Ingredient> getIngredients() const;
    
    std::vector<std::string> getCategories() const;

    const std::string& getDescription() const;

    const std::string& getImagePath() const;

    const unsigned getType() const;

    void output(std::ostream& s, unsigned indent = 0) const;

    void normalizeIngredient(std::string key, float amount);

  private:

    void addIngredient(Ingredient& ingredient);

    void addCategory(std::string category);

    // The unique drink key
    std::string mKey;

    // The drink name
    std::string mName;

    // Drink description
    std::string mDescription;

    // Drink image path
    std::string mImagePath;

    // Helps determine how to normalize the drink
    int mType;

    // The ingredient in the drink
    std::vector<Ingredient> mIngredients;
    
    // The categories the drink belongs to
    std::vector<std::string> mCategories;
};

#endif // DRINK_HPP
