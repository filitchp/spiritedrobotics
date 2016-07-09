#include "models/event.hpp"

#include <iostream>
#include <string>

#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>

using boost::property_tree::ptree;
using namespace std;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Event::Event(const ptree& pt)
{
  try
  {
    string type = pt.get<std::string>("type");

    if (type == "Lights")
    {
      mType = EventTypeLights;
    }
    else if (type == "MusicStart")
    {
      mType = EventTypeMusicStart;
    }
    else if (type == "MusicStop")
    {
      mType = EventTypeMusicStop;
    }
    // Ingredients get added dynamically, not from a config file...
//      else if (type == "Ingredient")
//      {
//        mType = DrinkTypeIngredient;
//      }
    else
    {
      // Invalid
      mType = -1;
    }
  }
  catch (boost::exception& e)
  {
    cerr << "ERROR: Could not read the event type" << endl;
    return;
  }

  try
  {
    mKey = pt.get<string>("key");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the event key " << endl;
  }

  try
  {
    mDuration = pt.get<unsigned>("duration");
  }
  catch (boost::exception& e)
  {
    cout << "ERROR: Could not get the event duration" << endl;
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Event::Event(unsigned type, string key, unsigned duration, float amount) :
    mType(type),
    mKey(key),
    mDuration(duration),
    mAmount(amount)
{
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const string& Event::getKey() const
{
  return mKey;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned Event::getDuration() const
{
  return mDuration;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
unsigned Event::setDuration(unsigned duration)
{
  mDuration = duration;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
float Event::getAmount() const
{
  return mAmount;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
const unsigned Event::getType() const
{
  return mType;
}
