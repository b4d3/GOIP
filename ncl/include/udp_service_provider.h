#pragma once

#include <string>
#include <functional>
#include <boost/asio.hpp>
#include <thread>

namespace goip {

    //a low-level class that provides the udp service
    //this class will be used to connect to both peers and the udp-server that gives the peer information
    //lacks error handling
    class udp_service_provider {
        public:
            //initializes everything needed to communicate with the peer on the given address and port
            //this class in initialized after the udp_connections_manager has been initialized to make sure the socket and io_service are shared
            udp_service_provider(boost::asio::io_service* io_service, boost::asio::ip::udp::socket* socket,
                const std::string& peer_ipv4_address, int peer_port_number);

            //this constructor blocks until it connects to a client that sends the expected_message
            udp_service_provider(boost::asio::io_service* io_service, boost::asio::ip::udp::socket* socket, std::string expected_message);


            //RAII for all the resources
            virtual ~udp_service_provider();

            //sends a given message to the peer
            void send_message_to_peer(const std::string& message);

            //blocks the calling thread until a single message has been received
            //and then calls the given callback
            //after that the control is return to the caller
            //returns if input_message_loop is running!
            void expect_single_message(std::function<void(const std::string& message)>& callback);

            //immediately returns to the caller
            //callback is called on separate thread once the message is received
            //returns if input_message_loop is running!
            void expect_single_message_async(std::function<void(const std::string& message)>& callback);

            //starts an infinite message loop on a separate thread
            //for each received message, the callback function is called
            //the caller is responsible for the termination of the loop
            void start_input_message_loop(std::function<void(const std::string& message)>& callback);

            //terminates the running input message loop
            //thread-safety not implemented yet!
            void terminate_input_message_loop();

        private:    
            //this function never returns, it is called by the start_input_message_loop
            void infinite_message_loop();
            
            std::function<void(const std::string& message)> callback;
            boost::asio::ip::udp::endpoint *remote_endpoint;
            std::thread *message_receiver_thread;
            boost::asio::io_service* io_service;
            boost::asio::ip::udp::socket* socket;   
            bool loop_running;         
    };
}