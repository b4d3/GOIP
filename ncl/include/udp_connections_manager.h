#pragma once

#include "udp_service_provider.h"
#include <string>
#include <boost/asio.hpp>
#include <vector>
#include <functional>

namespace goip {
    //This class manages all the connections from a single socket
    //it keeps a list of peers and sends a message to needed peer
    //at the moment, this list is kept inside a vector, later on a key-value pair (a map) should be used
    //to make the api better
    class udp_connections_manager {
        public:
            //creates a local socket that will be used by all the peers registered to this udp_connections_manager
            udp_connections_manager();

            //RAII stuff
            virtual ~udp_connections_manager();

            //add a new peer to the list
            //returns an int indicating the peer id
            //this id will be used by all the functions
            //this will later be turned into a key-value map
            int add_new_peer(const std::string& peer_ip_address, int peer_port_number);

            //sends a message to the peer with the given id
            void send_message_to_peer(int peer_number, const std::string& message);

            //blocks and waits for a single message from a given peer
            //after that, a callback is called on this thread and then the control is returned to the caller
            void expect_single_message_from_peer(int peer_number, std::function<void(const std::string& message)> callback_function);

            //start an infinite peer message loop on a separate thread
            void start_peer_message_loop(int peer_number, std::function<void(const std::string& message)> callback_function);

            //stops the infinite message loop for this peer
            void stop_peer_message_loop(int peer_number);

        private:
            boost::asio::io_service* io_service; 
            boost::asio::ip::udp::endpoint *local_endpoint;
            boost::asio::ip::udp::socket* socket;
            std::vector<udp_service_provider*> peer_list;
    };
}