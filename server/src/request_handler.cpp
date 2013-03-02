//
// request_handler.cpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "request_handler.hpp"

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"
#include "models/order.hpp"

using namespace std;

namespace http {
namespace server {

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
map<string, string> generateQueryMap(const string& query)
{
  vector<string> keyValueStrings;

  map<string, string> queryMap;

  boost::split(keyValueStrings, query, boost::is_any_of("&"));

  BOOST_FOREACH(string keyValueString, keyValueStrings)
  {
    vector<string> keyAndValue;

    boost::split(keyAndValue, keyValueString, boost::is_any_of("="));
    if (keyAndValue.size() == 2)
    {
      // DEBUG
//      cout << "KEY = " << keyAndValue[0] << endl;
//      cout << "VAL = " << keyAndValue[1] << endl;

      queryMap[keyAndValue[0]] = keyAndValue[1];
    }
  }

  return queryMap;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
request_handler::request_handler(const string& doc_root, DrinkManager& dm)
  : doc_root_(doc_root),
    mDrinkManager(dm)
{
}

//------------------------------------------------------------------------------
//RFC 3986 Section 3 visualizes the structure of URIs as follows:
//
//URL:      foo://example.com:8042/over/there?name=ferret#nose
//          \_/   \______________/\_________/ \_________/ \__/
//           |           |            |            |        |
//        scheme     authority       path        query   fragment
//------------------------------------------------------------------------------
void request_handler::handle_request(const request& req, reply& rep)
{

  // DEBUG
//  cout << "=================================" << endl;
//  cout << "METHOD = " << req.method << endl;
//  cout << "URI = " << req.uri << endl;
//
//  std::vector<header> vals = req.headers;
//
//  BOOST_FOREACH(header h, vals)
//  {
//    cout <<  "NAME = " << h.name << endl;
//    cout <<  "VALUE = " << h.value << endl;
//  }

  // Decode url to path.
  string path_and_query;
  if (!url_decode(req.uri, path_and_query))
  {
    rep = reply::stock_reply(reply::bad_request);
    return;
  }

  // Request path must be absolute and not contain "..".
  if (path_and_query.empty() || path_and_query[0] != '/'
      || path_and_query.find("..") != string::npos)
  {
    rep = reply::stock_reply(reply::bad_request);
    return;
  }

  // TODO: check for fragment and send error if exists
  const string drink_list_path("/drinkList");
  const string order_preset_drink_path("/orderPresetDrink");
  const string pending_orders_path("/pendingOrders");
  const string approved_orders_path("/approvedOrders");
  const string approve_order_path("/approveOrder");
  const string test_tower_path("/testTower");
  const string init_addresses_path("/initTowers");

  string path("");
  string query("");

  unsigned split = path_and_query.find("?");

  map<string, string> queryMap;

  if (split == string::npos)
  {
    // There is no query, just a path
    path = path_and_query;
  }
  else
  {
    path = path_and_query.substr(0, split);

    unsigned query_start = split + 1;
    unsigned query_len = path_and_query.size() - query_start;

    if (query_len)
    {
      // There is the URI query, get the parameters
      query = path_and_query.substr(query_start, query_len);
    }

    // DEBUG
//    cout << "path " << path  << endl;
//    cout << "query " << query << endl;

    // generate a key-value map for the URI query parameters
    queryMap = generateQueryMap(query);
  }

  // Parse the request
  if (path == drink_list_path)
  {
    //--------------------
    // Display drink list
    //--------------------
    handleDrinkListRequest(rep);
  }
  else if (path == order_preset_drink_path)
  {
    //--------------------
    // Handle drink order
    //--------------------
    handleOrderPresetDrinkRequest(queryMap, rep);
  }
  else if (path == pending_orders_path)
  {
    //----------------------------------------
    // Display a list of pending drink orders
    //----------------------------------------
    handlePendingOrdersRequest(rep);
  }
  else if (path == approved_orders_path)
  {
    //----------------------------------------
    // Display a list of approved drink orders
    //----------------------------------------
    handleApprovedOrdersRequest(rep);
  }
  else if (path == approve_order_path)
  {
    //----------------------------------------
    // Approve a pending drink
    //----------------------------------------
    handleApproveOrderRequest(queryMap,rep);
  }
  else if (path == test_tower_path)
  {
    //----------------------------------------
    // DEBUG: test a tower
    //----------------------------------------
    handleTestTowerRequest(queryMap,rep);
  }
  else if (path == init_addresses_path)
  {
    handleInitRoutineRequest(rep);
  }
  else
  {
    // The request was for a file...
    handle_file_request(path_and_query, req, rep);
  }
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleInitRoutineRequest(reply& rep)
{

  bool success = false;
  if (mDrinkManager.initTowers())
  {
    success = true;
  }


  if (success)
  {
    string successMessage = "{\"result\" : true}";
    rep.content.append(successMessage.c_str(), successMessage.size());
  }
  else
  {
    string errorMessage = "{\"result\" : false}";
    rep.content.append(errorMessage.c_str(), errorMessage.size());
  }

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleTestTowerRequest(map<string, string>& queryMap, reply& rep)
{
  bool success = false;

  if (queryMap.size())
  {
    string towerIdStr;
    string amountStr;

    if (queryMap.find("tower") != queryMap.end())
    {
      towerIdStr = queryMap["tower"];
    }

    if (queryMap.find("amount") != queryMap.end())
    {
      amountStr = queryMap["amount"];
    }

    if (towerIdStr.size() && amountStr.size())
    {
      cout << "towerIdStr " << towerIdStr << endl;
      cout << "amountStr " << amountStr << endl;

      unsigned towerId;
      istringstream ( towerIdStr ) >> towerId;

      float amount = boost::lexical_cast<float>(amountStr);

      // If we have a drink key, a customer name, and a timestamp
      if ((towerId >= 0) && (amount > 0))
      {
        cout << "towerId " << towerId << endl;
        cout << "amount " << amount << endl;

        if (mDrinkManager.testTower(towerId, amount))
        {
          success = true;
        }
      }
    }
  }

  if (success)
  {
    cout << "TEST SUCCESS" << endl;
    string successMessage = "{\"result\" : true}";
    rep.content.append(successMessage.c_str(), successMessage.size());
  }
  else
  {
    cout << "TEST FAILURE" << endl;
    string errorMessage = "{\"result\" : false}";
    rep.content.append(errorMessage.c_str(), errorMessage.size());
  }

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleApproveOrderRequest(map<string, string>& queryMap, reply& rep)
{
  bool success = false;

  if (queryMap.size())
  {
    string drinkKey;
    string customerName;
    unsigned timestamp;

    if (queryMap.find("key") != queryMap.end())
    {
      drinkKey = queryMap["key"];
    }

    if (queryMap.find("customer") != queryMap.end())
    {
      customerName = queryMap["customer"];
    }

    if (queryMap.find("timestamp") != queryMap.end())
    {
      timestamp = boost::lexical_cast<unsigned>(queryMap["timestamp"]);
    }

    // If we have a drink key, a customer name, and a timestamp
    if (drinkKey.size() && customerName.size())
    {
      cout << "drinkKey" << drinkKey << endl;
      cout << "customerName" << customerName << endl;
      cout << "timestamp" << timestamp << endl;

      if (mDrinkManager.approveOrder(drinkKey, customerName, timestamp))
      {
       success = true;
      }
    }
  }

  if (success)
  {
    string successMessage = "{\"result\" : true}";
    rep.content.append(successMessage.c_str(), successMessage.size());
  }
  else
  {
    string errorMessage = "{\"result\" : false}";
    rep.content.append(errorMessage.c_str(), errorMessage.size());
  }

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";

}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handlePendingOrdersRequest(reply& rep)
{

  stringstream oss(stringstream::out);

  mDrinkManager.outputPendingOrders(oss, 0);

  string message = oss.str();
  rep.content.append(message.c_str(), message.size());

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleApprovedOrdersRequest(reply& rep)
{

  stringstream oss(stringstream::out);

  mDrinkManager.outputApprovedOrders(oss, 0);

  string message = oss.str();
  rep.content.append(message.c_str(), message.size());

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleDrinkListRequest(reply& rep)
{
  stringstream oss(stringstream::out);

  mDrinkManager.outputDrinkList(oss, 0);

  string message = oss.str();
  rep.content.append(message.c_str(), message.size());

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handleOrderPresetDrinkRequest(map<string, string>& queryMap, reply& rep)
{
  bool success = false;

  if (queryMap.size())
  {
    string drinkKey;
    string customerName;

    if (queryMap.find("key") != queryMap.end())
    {
      drinkKey = queryMap["key"];
    }

    if (queryMap.find("customer") != queryMap.end())
    {
      customerName = queryMap["customer"];
    }

    // If we have both a drink key and a customer name
    if (drinkKey.size() && customerName.size())
    {

      struct timeval currentTime;

      gettimeofday(&currentTime, NULL);

      cout << "drinkKey" << drinkKey << endl;
      cout << "customerName" << customerName << endl;
      cout << "currentTime" << currentTime.tv_sec << endl;

      if (mDrinkManager.addOrder(drinkKey, customerName, (unsigned)currentTime.tv_sec))
      {
        success = true;
      }
    }
  }

  if (success)
  {
    string successMessage = "{\"result\" : true}";
    rep.content.append(successMessage.c_str(), successMessage.size());
  }
  else
  {
    string errorMessage = "{\"result\" : false}";
    rep.content.append(errorMessage.c_str(), errorMessage.size());
  }

  rep.status = reply::ok;

  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = "application/json";
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void request_handler::handle_file_request(
  string& path_and_query,
  const request& req,
  reply& rep)
{
  // If path ends in slash (i.e. is a directory) then add "index.html".
  if (path_and_query[path_and_query.size() - 1] == '/')
  {
    path_and_query += "index.html";
  }

  // Determine the file extension.
  size_t last_slash_pos = path_and_query.find_last_of("/");
  size_t last_dot_pos = path_and_query.find_last_of(".");
  string extension;

  if (last_dot_pos != string::npos && last_dot_pos > last_slash_pos)
  {
    extension = path_and_query.substr(last_dot_pos + 1);
  }

  // Open the file to send back.
  string full_path = doc_root_ + path_and_query;
  ifstream is(full_path.c_str(), ios::in | ios::binary);
  if (!is)
  {
    rep = reply::stock_reply(reply::not_found);
    return;
  }

  // Fill out the reply to be sent to the client.
  rep.status = reply::ok;
  char buf[512];
  while (is.read(buf, sizeof(buf)).gcount() > 0)
  {
    rep.content.append(buf, is.gcount());
  }
  rep.headers.resize(2);
  rep.headers[0].name = "Content-Length";
  rep.headers[0].value = boost::lexical_cast<string>(rep.content.size());
  rep.headers[1].name = "Content-Type";
  rep.headers[1].value = mime_types::extension_to_type(extension);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool request_handler::url_decode(const string& in, string& out)
{
  out.clear();
  out.reserve(in.size());
  for (size_t i = 0; i < in.size(); ++i)
  {
    if (in[i] == '%')
    {
      if (i + 3 <= in.size())
      {
        int value = 0;
        istringstream is(in.substr(i + 1, 2));
        if (is >> hex >> value)
        {
          out += static_cast<char>(value);
          i += 2;
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
    else if (in[i] == '+')
    {
      out += ' ';
    }
    else
    {
      out += in[i];
    }
  }
  return true;
}

} // namespace server
} // namespace http
