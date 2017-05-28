#include "../include/simple_udp_server_provider.h"
#include "../include/helper_functions.h"
#include <iostream>

int main()
{
  goip::simple_udp_server_provider simple_udp_server(2031);
  simple_udp_server.register_a_callback_function(callback_for_received_messages);


  char message[100];
  while(true) {
    std::cout << "Enter a message to send to the client: " << std::endl;
    std::cin.getline(message,sizeof(message));
    simple_udp_server.send_message_to_client(std::string(message) + "\n");
  }

  return 0;
}