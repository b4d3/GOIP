#pragma once

#include <udp_connections_manager.h>
//a place for functions so that main.cpp is not polluted

namespace goip
{

//blocking call - doesn't return until it connects to server
void establish_connection_to_server(udp_connections_manager &ucm, configuration_reader &config_reader, int &server_peer_id)
{
    server_peer_id = ucm.add_new_peer(config_reader.get_central_server_ip_address(), config_reader.get_central_server_port());
    std::string server_message = "ERROR!";

    while (server_message != "Connection to peer established!")
    {
        ucm.expect_single_message_from_peer(server_peer_id, [&](const std::string &message) {
            std::cout << message << std::endl;
            server_message = message;
        });
    }
}
}