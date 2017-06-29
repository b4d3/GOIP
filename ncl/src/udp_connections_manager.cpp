#include "../include/udp_connections_manager.h"
#include <iostream>

using namespace goip;

udp_connections_manager::udp_connections_manager(int local_port) : io_service{new boost::asio::io_service()},
                                                                   local_endpoint{new boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), local_port)},
                                                                   socket{new boost::asio::ip::udp::socket(*io_service, *local_endpoint)}
{

    //add error handling for when the port is taken!
}

udp_connections_manager::udp_connections_manager() : io_service{new boost::asio::io_service()},
                                                     local_endpoint{new boost::asio::ip::udp::endpoint()},
                                                     socket{new boost::asio::ip::udp::socket(*io_service)}
{

    //add error handling
}

//check if this destruction of vector elements is OK
udp_connections_manager::~udp_connections_manager()
{
    for (auto element : peer_list)
    {
        delete element;
    }
    delete io_service;
    delete local_endpoint;
    delete socket;
}

int udp_connections_manager::add_new_peer(const std::string &peer_ip_address, int peer_port_number)
{
    peer_list.push_back(new udp_service_provider(io_service, socket, peer_ip_address, peer_port_number));
    return peer_list.size() - 1;
}

int udp_connections_manager::add_new_peer(std::string &expected_message)
{
    peer_list.push_back(new udp_service_provider(io_service, socket, expected_message));
    std::cout << "Added a new local peer!" << std::endl;
    std::cout << "Peer list size now is " << peer_list.size();
    return peer_list.size() - 1;
}

void udp_connections_manager::send_message_to_peer(int peer_number, const std::string &message)
{
    peer_list[peer_number]->send_message_to_peer(message);
}

void udp_connections_manager::send_message_to_all(const std::string &message)
{
    std::cout << "Number of peers is " << peer_list.size() << std::endl;
    for (auto peer : peer_list)
    {
        std::cout << "Peer found here!" << std::endl;
        peer->send_message_to_peer(message);
    }
}

void udp_connections_manager::expect_single_message_from_peer(int peer_number, std::function<void(const std::string &)> callback_function)
{
    peer_list[peer_number]->expect_single_message(callback_function);
}

void udp_connections_manager::start_peer_message_loop(int peer_number, std::function<void(const std::string &)> callback_function)
{
    peer_list[peer_number]->start_input_message_loop(callback_function);
}

void udp_connections_manager::stop_peer_message_loop(int peer_number)
{
    peer_list[peer_number]->terminate_input_message_loop();
}