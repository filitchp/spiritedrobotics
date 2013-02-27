//
// request_handler.hpp
// ~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include <string>
#include <boost/noncopyable.hpp>
#include "drink_manager.hpp"

namespace http {
namespace server {

struct reply;
struct request;

/// The common handler for all incoming requests.
class request_handler : private boost::noncopyable
{
  public:
    /// Construct with a directory containing files to be served.
    explicit request_handler(const std::string& doc_root, DrinkManager& dm);

    /// Handle a request and produce a reply.
    void handle_request(const request& req, reply& rep);

  private:
    /// The directory containing the files to be served.
    std::string doc_root_;

    DrinkManager& mDrinkManager;

    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    static bool url_decode(const std::string& in, std::string& out);
    void handle_file_request(std::string& request_path, const request& req, reply& rep);

    void handleDrinkListRequest(reply& rep);
    void handlePendingOrdersRequest(reply& rep);
    void handleApprovedOrdersRequest(reply& rep);
    void handleOrderPresetDrinkRequest(std::map<std::string, std::string>& queryMap, reply& rep);
    void handleApproveOrderRequest(std::map<std::string, std::string>& queryMap, reply& rep);
};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
