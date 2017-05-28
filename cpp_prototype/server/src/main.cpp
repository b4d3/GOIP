#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "../include/simple_udp_server_provider.h"

using boost::asio::ip::udp;


int main()
{
  goip::simple_udp_server_provider simple_udp_server(13);
  simple_udp_server.expect_message();
  simple_udp_server.send_message_to_client("message from the server");
  // try
  // {
  //   boost::asio::io_service io_service;

  //   udp::endpoint a = udp::endpoint(udp::v4(), 2031);
  //   udp::socket socket(io_service, a);

  //   std::cout <<"Server is running!" << std::endl;

  //   for (;;)
  //   {
  //     boost::array<char, 128> recv_buf;
  //     udp::endpoint remote_endpoint;
  //     boost::system::error_code error;
  //     size_t len = socket.receive_from(boost::asio::buffer(recv_buf),
  //         remote_endpoint, 0, error);
  //     std::cout.write(recv_buf.data(), len);
  //     std::cout.flush();

  //     if (error && error != boost::asio::error::message_size)
  //       throw boost::system::system_error(error);

  //     std::string message = make_daytime_string();
  //     message = "got this message from server\n";

  //     boost::system::error_code ignored_error;
  //     socket.send_to(boost::asio::buffer(message),
  //         remote_endpoint, 0, ignored_error);
      
  //     // len = socket.receive_from(boost::asio::buffer(recv_buf),
  //     //     remote_endpoint, 0, error);

  //     len = socket.receive(boost::asio::buffer(recv_buf));

  //     std::cout.write(recv_buf.data(), len);
          
  //     // boost::asio::write(socket, boost::asio::buffer(message));
  //   }
  // }
  // catch (std::exception& e)
  // {
  //   std::cerr << e.what() << std::endl;
  // }

  return 0;
}