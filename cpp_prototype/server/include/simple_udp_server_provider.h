#include <boost/asio.hpp>

namespace goip {

    class simple_udp_server_provider {
        public:
            //constructor does not return until the client connects to it- this will be implemented on separate thread later
            explicit simple_udp_server_provider(int desired_port);
            
            //not implemented ATM, check needed to see what resources (if any) need to be released
            // virtual void ~simple_udp_server_provider();     
            
            //sends the message to the client, return type needs to indicate if the message was sent successfully
            //also, api should expose sending raw data, not std::string
            void send_message_to_client(std::string message);

            //prints out the message received from the client
            //later on, callback mechanism will be added to allow the user of this api to reponds to the message
            //this method does not return until it receives message from client
            void expect_message();

            //Creates a new thread and starts a infinite loop on that thread
            //To be implemented later: user of the API will set a callback function to be called on each received message
            void async_wait_for_message();

        private:
            boost::asio::io_service *io_service;
            boost::asio::ip::udp::endpoint *local_endpoint;
            boost::asio::ip::udp::endpoint *remote_endpoint;
            boost::asio::ip::udp::socket *socket;
    };
}