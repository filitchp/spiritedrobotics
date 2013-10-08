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
#include <boost/program_options.hpp>

#include "server.hpp"

using namespace boost::program_options;
using namespace boost::filesystem;
using namespace std;
using boost::property_tree::ptree;

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void showHelp(options_description& desc)
{
  cerr << desc << endl;
  cerr << " Examples: " << endl;
  cerr << endl;
  cerr << "  Localhost on port 3000 (IPv4):\n";
  cerr << "    ./Order_Server 127.0.0.1 3000 /var/www/spiritedrobotics/web/" << endl;
  cerr << endl;
  cerr << "  Localhost on port 3000 (IPv6):\n";
  cerr << "    ./Order_Server ::1 3000 /var/www/spiritedrobotics/web/" << endl;
  cerr << endl;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  try
  {
    positional_options_description p;
    p.add("host", 1);
    p.add("port", 1);
    p.add("root", 1);

    options_description desc("Arguments");

    desc.add_options()
        ("help", "Produce this help message")
        ("host", value< string >(), "The IP address of the server")
        ("port", value< string >(), "The port the server will listen on")
        ("root", value< string >(), "The document root of the server files")
        ("demo,d", "Run the server in demo mode, so that no orders are processed");

    variables_map vm;

    store(command_line_parser(argc, argv).options(desc).positional(p).run(), vm);

    notify(vm);

    string host;
    string port;
    string root;
    bool demoMode = false;

    if (vm.count("help"))
    {
      showHelp(desc);
      return 1;
    }

    if (vm.count("demo"))
    {
      demoMode = true;
    }

    if (vm.count("host"))
    {
      //cout << "Host: " << vm["host"].as<string>() << endl;
      host = vm["host"].as<string>();
    }
    else
    {
      cout << "You must provide an IP address for the host" << endl << endl;
      showHelp(desc);
      return 1;
    }

    if (vm.count("port"))
    {
      //cout << "port: " << vm["port"].as<string>() << endl;
      port = vm["port"].as<string>();
    }
    else
    {
      cout << "You must provide a port" << endl;
      showHelp(desc);
      return 1;
    }

    if (vm.count("root"))
    {
      //cout << "root: " << vm["root"].as<string>() << endl;
      root = vm["root"].as<string>();
    }
    else
    {
      cout << "You must provide a root directory" << endl;
      showHelp(desc);
      return 1;
    }

    // Initialize the server.
    http::server::server s(host, port, root, demoMode);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}



