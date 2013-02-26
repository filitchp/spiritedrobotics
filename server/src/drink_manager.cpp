#include "drink_manager.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>


using namespace boost::filesystem;
using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
DrinkManager::DrinkManager(const string& rootPath)
{

  stringstream configFilePath(stringstream::out);
  configFilePath << rootPath << "/assets/json/barbot.json";

  readSystemConfiguration(configFilePath.str());

  stringstream drinksPath(stringstream::out);
  drinksPath << rootPath << "/assets/json/drinks";

  readAllDrinks(drinksPath.str());

  // DEBUG
  //outputDrinkList(cout, 0);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::readSystemConfiguration(string systemConfigurationPath)
{
  // Create an empty property tree object
  ptree pt;

  // Parse the system configuration file
  read_json(systemConfigurationPath, pt);

  // Create the system configuration object
  mpBarbot = new BarBot(pt);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::readAllDrinks(string pathDrinkDirectory)
{
  path p(pathDrinkDirectory);

  vector<path> drinkPaths;
  try
  {
    // If the path exists and is a directory
    if (exists (p) && is_directory(p))
    {
      // DEBUG
      //cout << p << " is a directory containing:" << endl;
      //copy(directory_iterator(p), directory_iterator(), ostream_iterator<directory_entry>(cout, "\n"));

      // Store all paths in a vector
      copy(directory_iterator(p), directory_iterator(), back_inserter(drinkPaths));
    }
    else
    {
      cout << p << " does not exist\n";
    }
  }
  catch (const filesystem_error& ex)
  {
    cout << ex.what() << endl;
  }

  for (vector<path>::const_iterator it(drinkPaths.begin()); it != drinkPaths.end(); ++it)
  {
    path drinkPath = *it;

    cout << "   " << drinkPath.filename() << '\n';

    ptree dpt;
    read_json(drinkPath.string(), dpt);

    Drink drink(dpt);

    mAllDrinks.push_back(drink);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::approveOrder(string drinkKey, string customerName, unsigned timestamp)
{
  string orderId = Order::generateOrderId(drinkKey, customerName, timestamp);

  map<string, Order>::iterator it = mPendingOrders.find(orderId);

  // If the order does not exist
  if (it == mPendingOrders.end())
  {
    return false;
  }

  // MAKE THE DRINK HERE!
  Order theOrderToMake = it->second;


  mApprovedOrders.insert(pair<string, Order>(it->first, it->second));

  mPendingOrders.erase(it);

  return true;

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::addOrder(string drinkKey, string customerName, unsigned timestamp)
{

  vector<Ingredient> ingredients;

  // Grab the ingredients from the drink key provided
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey() == drinkKey)
    {
      ingredients = d.getIngredients();
      break;
    }
  }

  // If there are no ingredients for this preset (or the preset does not exist)
  if (ingredients.size() == 0)
  {
    return false;
  }

  Order newOrder(drinkKey, customerName, timestamp, ingredients);

  string orderId = newOrder.getOrderId();

  // If the order ID is unique
  if (mPendingOrders.find(orderId) == mPendingOrders.end())
  {
    // Add the order
    mPendingOrders.insert(std::pair<string, Order>(orderId, newOrder));
  }
  else
  {
    // The order already exists
    // This could happen if the same order gets submitted back-to-back
    // Drunk proof design!!!
    return false;
  }

  return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputPendingOrders(std::ostream& s, unsigned indent)
{
  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;

  typedef std::map<std::string, Order> order_map;

  BOOST_FOREACH(const order_map::value_type& orderPair, mPendingOrders)
  {
    Order o = orderPair.second;

    o.output(s, indent + 4);

    count++;

    if (count != mPendingOrders.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputApprovedOrders(std::ostream& s, unsigned indent)
{
  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;

  typedef std::map<std::string, Order> order_map;

  BOOST_FOREACH(const order_map::value_type& orderPair, mApprovedOrders)
  {
    Order o = orderPair.second;

    o.output(s, indent + 4);

    count++;

    if (count != mApprovedOrders.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;
}


//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool DrinkManager::getIngredientsForDrinkKey(string key, vector<Ingredient>& ingredients)
{
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    if (d.getKey() == key)
    {
      ingredients = d.getIngredients();
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DrinkManager::outputDrinkList(ostream& s, unsigned indent)
{

  string p = string(indent, ' ');

  s << p << "["  << endl;

  unsigned count = 0;
  BOOST_FOREACH(const Drink& d, mAllDrinks)
  {
    d.output(s, indent + 4);

    count++;
    if (count != mAllDrinks.size())
    {
      s << "," << endl;
    }
    else
    {
      s << endl;
    }
  }

  s << p << "]" << endl;

}


