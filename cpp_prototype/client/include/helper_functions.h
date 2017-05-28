#include <iostream>
#include <boost/array.hpp>

void callback_for_received_messages(boost::array<char, 128> message, size_t len) {
  std::cout <<"Got this message from the server: ";
  std::cout.write(message.data(), len);
}