#include "../include/simple_udp_client.h"

using boost::asio::ip::udp;

int main(int argc, char* argv[])
{
  goip::simple_udp_client udp_client("127.0.0.1", 2031);
  udp_client.send_message("test is called\n");
  udp_client.expect_and_print_message();
  
  return 0;
}