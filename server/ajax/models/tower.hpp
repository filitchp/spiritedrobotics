#ifndef TOWER_HPP
#define TOWER_HPP

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
class Tower
{
  public:
    Tower(const boost::property_tree::ptree& pt);

    unsigned getTowerId() const;
    float getFlowRate() const;
    const std::string& getIngredientName() const;
    const std::string& getIngredientKey() const;

  private:

    // The tower ID (corresponds to the towers order in the chain)
    unsigned mTowerId;

    // Calibration variable to determine the pump timing (milliseconds per ounce)
    float mFlowRate;

    // The ingredient name in the tower
    std::string mIngredientName;

    // The ingredient key in the tower
    std::string mIngredientKey;

};

#endif // TOWER_HPP
