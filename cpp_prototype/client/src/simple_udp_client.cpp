#include "../include/simple_udp_client.h"
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <functional>


using namespace goip;

simple_udp_client::simple_udp_client(std::string ip_v4_address, int port_number): 
        io_service{new boost::asio::io_service()}, socket{new boost::asio::ip::udp::socket(*io_service)} {
    
    boost::asio::ip::address a = boost::asio::ip::address::from_string(ip_v4_address);
    remote_endpoint = new boost::asio::ip::udp::endpoint(a, port_number);
    socket->connect(*remote_endpoint);

    //sending an initial empty message because the server needs it to set its remote_endpoint
    //this logic needs to be checked later, and likely fixed
    send_message("");

    //initialize the listener
    sync_receiver_thread = new std::thread(std::bind(&simple_udp_client::expect_message_infite_loop, this));    

}

simple_udp_client::~simple_udp_client() {
    sync_receiver_thread->join();
}

void simple_udp_client::send_message(std::string message) {
    socket->send(boost::asio::buffer(message));
}

void simple_udp_client::expect_and_print_message() {
    boost::array<char, 128> recv_buffer;
    size_t len = socket->receive(boost::asio::buffer(recv_buffer));
    std::cout.write(recv_buffer.data(), len);
}

void simple_udp_client::expect_message_infite_loop() {
    boost::array<char, 128> recv_buffer;
    while (true) {
        size_t len = socket->receive(boost::asio::buffer(recv_buffer));
        received_message_callback_function(recv_buffer, len);
    }
}

void simple_udp_client::register_a_callback_function(std::function<void(boost::array<char, 128>, size_t)> callback_function) {
    received_message_callback_function = callback_function;
}
