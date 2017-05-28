#include <boost/asio.hpp>
#include <thread>
#include <functional>

namespace goip {

    class simple_udp_server_provider {
        public:
            //constructor does not return until the client connects to it- this will be implemented on separate thread later
            explicit simple_udp_server_provider(int desired_port);
            
            //not implemented ATM, check needed to see what resources (if any) need to be released
            virtual ~simple_udp_server_provider();     
            
            //sends the message to the client, return type needs to indicate if the message was sent successfully
            //also, api should expose sending raw data, not std::string
            void send_message_to_client(std::string message);

            //prints out the message received from the client
            //this method does not return until it receives message from client
            void expect_and_print_a_single_message();

            //this method will not return, it will run in an infinite loop and wait for messages
            //this should be opened on a separate thread
            //WARNING: when called from main thread crushes the program
            void expect_message_infinite_loop();

            //Creates a new thread and starts a infinite loop on that thread
            //To be implemented later: user of the API will set a callback function to be called on each received message
            //WARNING: when called from main thread crushes the program
            void async_wait_for_message();

            //Registers the callback function to be called for any received messages
            //ATM this function will block the receiver_thread, later on an option should be added to run it on a separate thread
            void register_a_callback_function(std::function<void(boost::array<char, 128>, size_t)> callback_function);

        private:
            boost::asio::io_service *io_service;
            boost::asio::ip::udp::endpoint *local_endpoint;
            boost::asio::ip::udp::endpoint *remote_endpoint;
            boost::asio::ip::udp::socket *socket;
            std::thread *sync_receiver_thread;
            std::function<void(boost::array<char, 128>, size_t)> received_message_callback_function;
    };
}