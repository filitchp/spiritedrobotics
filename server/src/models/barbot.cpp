#include "models/barbot.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>

using boost::property_tree::ptree;
using namespace std;

// Tower exception
struct tower_error: virtual boost::exception { };

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
BarBot::BarBot(const ptree& pt)
{

  try
  {
    mDescription = pt.get<std::string>("description");
    cout << "description: " << mDescription << endl;
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not read the BarBot configuration description" << endl;
    return;
  }

  try
  {
    // For each set of tower properties
    BOOST_FOREACH (const ptree::value_type& node, pt.get_child("towers"))
    {
      const ptree& towerProperties = node.second;

      Tower tower(towerProperties);

      addTower(tower);
    }
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not read tower properties" << endl;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void BarBot::addTower(Tower& tower)
{
  // Make sure the tower has unique values
  BOOST_FOREACH(const Tower& t, mTowers)
  {
    if (tower.getTowerId() == t.getTowerId())
    {
      cerr << "ERROR: Cannot have the same ID for two different towers";

      // TODO: throw exception
      return;
    }

    if (tower.getIngredientKey() == t.getIngredientKey())
    {
      cerr << "ERROR: Cannot have the same ingredient in two different towers";

      // TODO: throw exception
      return;
    }
  }

  mTowers.push_back(tower);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const Tower& BarBot::getTowerById(unsigned int id) const
{
  BOOST_FOREACH(const Tower& t, mTowers)
  {
    if (t.getTowerId() == id)
    {
      return t;
    }
  }

  // TODO: add exception details
  throw tower_error();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const Tower& BarBot::getTowerByIngredientKey(const std::string& ingredientKey) const
{
  BOOST_FOREACH(const Tower& t, mTowers)
  {
    if (t.getIngredientKey() == ingredientKey)
    {
      return t;
    }
  }
  cout << ingredientKey << endl;
  // TODO: add exception details
  throw tower_error();
}
