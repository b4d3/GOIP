#include "../include/simple_udp_server_provider.h"
#include "../include/helper_functions.h"
#include <iostream>

int main()
{
  goip::simple_udp_server_provider simple_udp_server(2031);
  std::string message;
  while(true) {
    std::cout << "Enter a message to send to the client" << std::endl;
    std::cin >> message;
    simple_udp_server.send_message_to_client(message);
  }

  return 0;
}