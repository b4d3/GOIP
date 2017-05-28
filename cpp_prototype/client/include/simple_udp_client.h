#include <string>
#include <boost/asio.hpp>

namespace goip {
    class simple_udp_client {
        public:
            //Constructor creates a simple udp client. This is a blocking call, it will return once the client is connected to the server.
            simple_udp_client(std::string ip_v4_address, int port_number);
            
            //not implemented ATM, to be checked later what resources need to be released
            virtual ~simple_udp_client();
            
            //sends a message to the client once the connection is established. API needs to be changed later to send raw data instead of std::string.
            void send_message(std::string message);

            //blocks until it receives a message from the server and then prints out the message. A callback mechanism will be implemented later to make sure
            //the user of the API can respond to the messages
            void expect_and_print_message();

        private:
            boost::asio::io_service *io_service;
            boost::asio::ip::udp::socket *socket;
            boost::asio::ip::udp::endpoint *endpoint;
    };
}