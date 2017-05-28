#include "../include/simple_udp_server_provider.h"
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <functional>

using namespace goip;


void handler(const boost::system::error_code& error, std::size_t bytes_transferred) {
    // std::cout.write(recv_buf.data(), len);
    std::cout <<"len is: " << bytes_transferred << std::endl;
}


simple_udp_server_provider::simple_udp_server_provider(int desired_port): 
        io_service{new boost::asio::io_service()},
        local_endpoint{new boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), desired_port)},
        socket{new boost::asio::ip::udp::socket(*io_service, *local_endpoint)},
        remote_endpoint{new boost::asio::ip::udp::endpoint()} {

    //not sure if this is the best possible implementation, it is the only one i got working ATM
    //the server needs to receive a message from client to save that client info in the remote_endpoint variable
    boost::array<char, 1> recv_buf;
    socket->receive_from(boost::asio::buffer(recv_buf), *remote_endpoint);
    socket->connect(*remote_endpoint);
    sync_receiver_thread = new std::thread(std::bind(&simple_udp_server_provider::expect_message_infinite_loop, this));    
}

simple_udp_server_provider::~simple_udp_server_provider() {
    //this line will cause the program to run in an infinite loop
    sync_receiver_thread->join();
}

void simple_udp_server_provider::send_message_to_client(std::string message) {
    socket->send(boost::asio::buffer(message));
}

void simple_udp_server_provider::expect_message_infinite_loop() {
    boost::array<char, 128> recv_buf;
    while (true) {
        size_t len = socket->receive(boost::asio::buffer(recv_buf));
        std::cout.write(recv_buf.data(), len);
    }
  
}
void simple_udp_server_provider::expect_and_print_a_single_message() {
    boost::array<char, 128> recv_buf;
    size_t len = socket->receive(boost::asio::buffer(recv_buf));
    received_message_callback_function(recv_buf, len);
    // std::cout.write(recv_buf.data(), len);
}


void simple_udp_server_provider::async_wait_for_message() {
    boost::array<char, 128> recv_buf;
    while (true) {
        socket->async_receive(boost::asio::buffer(recv_buf), handler);
        io_service->run();
    }    
}

void simple_udp_server_provider::register_a_callback_function(std::function<void(boost::array<char, 128>, size_t)> callback_function) {
    received_message_callback_function = callback_function;
}
