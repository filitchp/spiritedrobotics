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
#include <boost/lexical_cast.hpp>
#include "mime_types.hpp"
#include "reply.hpp"
#include "request.hpp"

using namespace std;

namespace http {
namespace server {

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

  string path("");
  string query("");

  unsigned split = path_and_query.find("?");

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
      // There is a query, get the parameters
      query = path_and_query.substr(query_start, query_len);
    }
  }

  // Parse the request
  if (path == drink_list_path)
  {
    cout << "path " << path  << endl;
    cout << "query " << query << endl;

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
  else
  {
    // The request was for a file...
    handle_file_request(path_and_query, req, rep);
  }
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
