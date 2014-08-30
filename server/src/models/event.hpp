#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

enum
{
  EventTypeLights = 0,
  EventTypeMusicStart = 1,
  EventTypeMusicStop = 2,
  EventTypeIngredient = 3
};

//------------------------------------------------------------------------------
// Describes an event in the time sequence.  An event can include setting
// lights, initialing a ingredient from a tower, playing music, etc
//------------------------------------------------------------------------------
class Event
{
  public:

    Event(const boost::property_tree::ptree& pt);

    Event(unsigned type, std::string key, unsigned duration, float amount);

    const unsigned getType() const;

    const std::string& getKey() const;

    unsigned getDuration() const;
    unsigned setDuration(unsigned duration);

    float getAmount() const;

  private:

    // The event key (event specific)
    std::string mKey;

    // The event type
    unsigned mType;

    // The length of time in milliseconds of this event
    // (in reality this is the time before the start of the next event)
    unsigned mDuration;

    // The amount of the event (if applicable)
    float mAmount;

};

#endif // EVENT_HPP
