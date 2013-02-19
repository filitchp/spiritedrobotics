//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/exception/info.hpp>
#include <boost/exception/error_info.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>

#include "server.hpp"
#include "models/barbot.hpp"
#include "models/drink.hpp"

using namespace boost::filesystem;
using namespace std;
using boost::property_tree::ptree;

// TODO: refactor out these globals

// System configuration
BarBot* barbot = NULL;

// All of the drinks from the drink library
vector<Drink> mAllDrinks;

// Drinks that can actually be made given the ingredients
vector<Drink> mValidDrinks;

void readSystemConfiguration(string path);

void readAllDrinks(string path);

//void readDrinkMenu(string path);

void outputDrinkList(ostream& s, unsigned indent = 0);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 4)
    {
      cerr << "Usage: http_server <address> <port> <doc_root>\n";
      cerr << "  For IPv4, try:\n";
      cerr << "    receiver 0.0.0.0 80 .\n";
      cerr << "  For IPv6, try:\n";
      cerr << "    receiver 0::0 80 .\n";
      return 1;
    }

    readSystemConfiguration("/var/www/spiritedrobotics/server/assets/barbot.json");

    readAllDrinks("/var/www/spiritedrobotics/server/assets/drinks/");

    //ptree pt;
    //mAllDrinks[0].output(cout, 0);
    //write_json(cout, pt);

    outputDrinkList(cout, 0);

    // Initialize the server.
    http::server::server s(argv[1], argv[2], argv[3]);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readSystemConfiguration(string systemConfigurationPath)
{
  // Create an empty property tree object
  ptree pt;

  // Parse the system configuration file
  read_json(systemConfigurationPath, pt);

  // Create the system configuration object
  barbot = new BarBot(pt);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void readAllDrinks(string pathDrinkDirectory)
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
void outputDrinkList(ostream& s, unsigned indent)
{

  string p = string(indent, ' ');

  s << p << "{" << endl;
  s << p << "  \"drinks\" : " << endl;
  s << p << "  ["  << endl;

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

  s << p << "  ]" << endl;
  s << p << "}" << endl;
}

