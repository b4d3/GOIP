#include <string>
#include <boost/asio.hpp>
#include <functional>
#include <thread>

namespace goip {
    class simple_udp_client {
        public:
            //Constructor creates a simple udp client. This is a blocking call, it will return once the client is connected to the server.
            simple_udp_client(std::string ip_v4_address, int port_number);
            
            //not implemented ATM, to be checked later what resources need to be released
            virtual ~simple_udp_client();
            
            //sends a message to the client once the connection is established. API needs to be changed later to send raw data instead of std::string.
            void send_message(std::string message);

            //blocks until it receives a message from the server and then prints out the message
            void expect_and_print_message();

            //enters an infinite loop and waits there for the incoming messages
            //sends the message to the registered callback. ATM, no check is done to see if the callback function is set, so the application will crash  if it is not
            //should not be called from the main thread because application will crash
            void expect_message_infite_loop();

            //Registers the callback function to be called for any received messages
            //ATM this function will block the receiver_thread, later on an option should be added to run it on a separate thread
            void register_a_callback_function(std::function<void(boost::array<char, 128>, size_t)> callback_function);

        private:
            boost::asio::io_service *io_service;
            boost::asio::ip::udp::socket *socket;
            boost::asio::ip::udp::endpoint *remote_endpoint;
            std::thread *sync_receiver_thread;
            std::function<void(boost::array<char, 128>, size_t)> received_message_callback_function;

    };
}