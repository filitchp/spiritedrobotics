#include "models/drink.hpp"

#include <iostream>
#include <string>
#include <ostream>

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
    mImagePath = pt.get<std::string>("imagePath");
    cout << "image path: " << mImagePath << endl;
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
// Unfortunately writing JSON from property trees has some limitations so
// for now we output it manually.  At least this is fast....
//------------------------------------------------------------------------------
void Drink::output(ostream& s, unsigned indent) const
{
  string p = string(indent, ' ');

  s << p << "{" << endl;
  s << p << "  \"key\" : \""         << mKey          << "\"," << endl;
  s << p << "  \"name\" : \""        << mName         << "\"," << endl;
  s << p << "  \"description\" : \"" << mDescription  << "\"," << endl;
  s << p << "  \"imagePath\" : \""   << mImagePath    << "\"," << endl;
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

// Doesn't quite work... In addition BOOST outputs everything as a string
//  pt.put("key", mKey);
//  pt.put("name", mName);
//  pt.put("description", mDescription);
//  pt.put("imagePath", mImagePath);
//
//  ptree ipts;
//  BOOST_FOREACH(const Ingredient& i, mIngredients)
//  {
//    ptree ipt;
//
//    i.output(ipt);
//
//    ipts.add_child("", ipt);
//
//  }
//
//  pt.add_child("ingredients", ipts);

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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
vector<Ingredient> Drink::getIngredients() const
{
  return mIngredients;
}