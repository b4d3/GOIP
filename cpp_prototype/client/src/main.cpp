#include "../include/simple_udp_client.h"
#include "../include/helper_functions.h"
#include <iostream>
#include <string> 

int main(int argc, char* argv[])
{
  goip::simple_udp_client udp_client("127.0.0.1", 2031);
  udp_client.register_a_callback_function(callback_for_received_messages);

  char message[100];

  while (true) {
    std::cout <<"Enter a message to send" << std::endl;
    
    //This is a bit messy, but using only cin breaks the message by spaces
    //Should check if cin >> can ignore spaces 
    std::cin.getline(message,sizeof(message));
    udp_client.send_message(std::string(message) + "\n");
  }
  
  return 0;
}