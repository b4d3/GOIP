#include "../include/simple_udp_server_provider.h"

using boost::asio::ip::udp;


int main()
{
  goip::simple_udp_server_provider simple_udp_server(2031);
  // simple_udp_server.expect_message();
  simple_udp_server.async_wait_for_message();
  simple_udp_server.send_message_to_client("message from the server\n");

  return 0;
}