#ifndef DRINK_MANAGER_HPP
#define DRINK_MANAGER_HPP

#include <string>
#include <vector>

#include <boost/property_tree/ptree.hpp>

#include "models/barbot.hpp"
#include "models/drink.hpp"

//------------------------------------------------------------------------------
// Describes the recipe for a drink
//------------------------------------------------------------------------------
class DrinkManager
{
  public:

    DrinkManager(const std::string& rootPath);

    //std::string getDrinkList() const;

    void outputDrinkList(std::ostream& s, unsigned indent);

  private:

    // System configuration
    BarBot* mpBarbot;

    // All of the drinks from the drink library
    std::vector<Drink> mAllDrinks;

    // Drinks that can actually be made given the ingredients
    std::vector<Drink> mValidDrinks;

    void readSystemConfiguration(std::string systemConfigurationPath);
    void readAllDrinks(std::string systemConfigurationPath);

};

#endif // DRINK_MANAGER_HPP
