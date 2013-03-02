#include "models/tower.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>

using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Tower::Tower(const ptree& pt)
{
  try
  {
    mIngredientName = pt.get<string>("name");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the ingredient name" << endl;
  }

  try
  {
    mIngredientKey = pt.get<string>("key");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the ingredient key " << endl;
  }

  try
  {
    mTowerId = pt.get<unsigned int>("id");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: could not get the tower ID" << endl;
  }

  try
  {
    mFlowRate = pt.get<float>("flowRate");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the flow rate" << endl;
  }

  // DEBUG
  //cout << "mIngredientName: " << mIngredientName << endl;
  //cout << "mIngredientKey: "  << mIngredientKey << endl;
  //cout << "mTowerId: "        << mTowerId << endl;
  //cout << "mFlowRate: "       << mFlowRate << endl;

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned Tower::getTowerId() const
{
  return mTowerId;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
float Tower::getFlowRate() const
{
  return mFlowRate;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Tower::getIngredientName() const
{
  return mIngredientName;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Tower::getIngredientKey() const
{
  return mIngredientKey;
}
