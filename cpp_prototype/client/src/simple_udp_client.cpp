#include "../include/simple_udp_client.h"
#include <iostream>
#include <string>
#include <boost/array.hpp>


using namespace goip;

simple_udp_client::simple_udp_client(std::string ip_v4_address, int port_number): 
        io_service{new boost::asio::io_service()}, socket{new boost::asio::ip::udp::socket(*io_service)} {
    
    std::cout <<"Called the simple_udp_client constructor. The server is located at " <<ip_v4_address <<":" <<port_number << std::endl;
    boost::asio::ip::address a = boost::asio::ip::address::from_string(ip_v4_address);
    endpoint = new boost::asio::ip::udp::endpoint(a, port_number);
    socket->connect(*endpoint);
}

simple_udp_client::~simple_udp_client() {

}

void simple_udp_client::send_message(std::string message) {
    socket->send(boost::asio::buffer(message));
    expect_and_print_message();
}

void simple_udp_client::expect_and_print_message() {
    boost::array<char, 128> recv_buffer;
    size_t len = socket->receive(boost::asio::buffer(recv_buffer));
    std::cout.write(recv_buffer.data(), len);
}