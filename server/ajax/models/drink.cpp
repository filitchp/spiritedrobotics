#include "models/drink.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Drink::Drink(const ptree& pt)
{
  try
  {
    mKey = pt.get<std::string>("key");
    cout << "mKey: " << mKey << endl;
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read the drink key" << endl;
    return;
  }

  try
  {
    mName = pt.get<std::string>("name");
    cout << "mName: " << mName << endl;
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read the drink name" << endl;
    return;
  }

  try
  {
    mDescription = pt.get<std::string>("description");
    cout << "description: " << mDescription << endl;
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read the drink description" << endl;
    return;
  }

  try
  {
    mDescription = pt.get<std::string>("imagePath");
    cout << "description: " << mDescription << endl;
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read the drink image path" << endl;
    return;
  }

  // Get the ingredients
  try
  {
    // For each set of ingredient properties
    BOOST_FOREACH (const ptree::value_type& node, pt.get_child("ingredients"))
    {
      const ptree& ingredientProperties = node.second;

      Ingredient ingredient(ingredientProperties);

      addIngredient(ingredient);
    }
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read ingredient properties" << endl;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Drink::addIngredient(Ingredient& ingredient)
{
  // Make sure the tower has unique values
  BOOST_FOREACH(const Ingredient& i, mIngredients)
  {

    if (ingredient.getKey() == i.getKey())
    {
      cerr << "ERROR: Cannot have two sets of the same ingredient in a drink";

      // TODO: throw exception
      return;
    }
  }

  mIngredients.push_back(ingredient);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Drink::getName() const
{
  return mName;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Drink::getKey() const
{
  return mKey;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Drink::getDescription() const
{
  return mDescription;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Drink::getImagePath() const
{
  return mImagePath;
}
