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

using namespace boost::filesystem;
using namespace std;
using boost::property_tree::ptree;


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
      cerr <<  endl;
      cerr << "Known Working Example: 127.0.0.1 3000 /var/www/spiritedrobotics/web/" << endl;
      return 1;
    }

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



