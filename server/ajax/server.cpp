//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "server.hpp"
#include <boost/bind.hpp>
#include <signal.h>

namespace http {
namespace server {

server::server(
    const std::string& address,
    const std::string& port,
    const std::string& doc_root)
  : mIOService(),
    mSignals(mIOService),
    mAcceptor(mIOService),
    mConnectionManager(),
    mpNewConnection(),
    mDrinkManager(doc_root),
    mRequestHandler(doc_root, mDrinkManager)
{

  // Register to handle the signals that indicate when the server should exit.
  // It is safe to register for the same signal multiple times in a program,
  // provided all registration for the specified signal is made through Asio.
  mSignals.add(SIGINT);
  mSignals.add(SIGTERM);
#if defined(SIGQUIT)
  mSignals.add(SIGQUIT);
#endif // defined(SIGQUIT)
  mSignals.async_wait(boost::bind(&server::handle_stop, this));

  // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
  boost::asio::ip::tcp::resolver resolver(mIOService);
  boost::asio::ip::tcp::resolver::query query(address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
  mAcceptor.open(endpoint.protocol());
  mAcceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  mAcceptor.bind(endpoint);
  mAcceptor.listen();

  start_accept();
}

void server::run()
{
  // The io_service::run() call will block until all asynchronous operations
  // have finished. While the server is running, there is always at least one
  // asynchronous operation outstanding: the asynchronous accept call waiting
  // for new incoming connections.
  mIOService.run();
}

void server::start_accept()
{
  mpNewConnection.reset(new connection(mIOService,
        mConnectionManager, mRequestHandler));

  mAcceptor.async_accept(mpNewConnection->socket(),
      boost::bind(&server::handle_accept, this,
        boost::asio::placeholders::error));
}

void server::handle_accept(const boost::system::error_code& e)
{
  // Check whether the server was stopped by a signal before this completion
  // handler had a chance to run.
  if (!mAcceptor.is_open())
  {
    return;
  }

  if (!e)
  {
    mConnectionManager.start(mpNewConnection);
  }

  start_accept();
}

void server::handle_stop()
{
  // The server is stopped by canceling all outstanding asynchronous
  // operations. Once all operations have finished the io_service::run() call
  // will exit.
  mAcceptor.close();
  mConnectionManager.stop_all();
}

} // namespace server
} // namespace http
