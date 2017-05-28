//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include "../include/simple_udp_client.h"

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
  goip::simple_udp_client udp_client("127.0.0.1", 2031);
  udp_client.send_message("test is called\n");

  return 0;
}