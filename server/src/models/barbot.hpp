#ifndef BARBOT_HPP
#define BARBOT_HPP

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "models/tower.hpp"

//------------------------------------------------------------------------------
// Describes the configuration of the entire system
//------------------------------------------------------------------------------
class BarBot
{
  public:

    BarBot(const boost::property_tree::ptree& pt);

    // Determines if BarBot can actually make this drink
    //bool drinkAvailable(const Drink& drink);

    //void exportLog(const std::string& filename);

    const Tower& getTowerById(unsigned int) const;
    const Tower& getTowerByIngredientKey(const std::string& ingredientKey) const;
    bool isTowerIdValid(unsigned char id) const;

  private:

    void addTower(Tower& tower);

    // The towers
    std::vector<Tower> mTowers;

    // A description of the current configuration
    std::string mDescription;
};

#endif // BARBOT_HPP
