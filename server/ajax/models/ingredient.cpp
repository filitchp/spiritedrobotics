#include "models/ingredient.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>

using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Ingredient::Ingredient(const ptree& pt)
{
  try
  {
    mName = pt.get<string>("name");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the ingredient name" << endl;
  }

  try
  {
    mKey = pt.get<string>("key");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the ingredient key " << endl;
  }

  try
  {
    mAmount = pt.get<float>("amount");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the ingredient amount" << endl;
  }

  cout << "mName:   " << mName << endl;
  cout << "mKey:    " << mKey << endl;
  cout << "mAmount: " << mAmount << endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Ingredient::getName() const
{
  return mName;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Ingredient::getKey() const
{
  return mKey;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
float Ingredient::getAmount() const
{
  return mAmount;
}
