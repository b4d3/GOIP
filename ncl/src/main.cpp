#include <iostream>
#include <string>
#include <algorithm>
#include <udp_connections_manager.h>
#include <udp_service_provider.h>
#include <configuration_reader.h>
#include <utils.h>

using namespace goip;

int main()
{
    //provide no filename so that the defualt configuration file is used
    configuration_reader config_reader;
    config_reader.print_configuration();

    //creates the udp_connection_manager that listens on a local port which is set in the configuration
    udp_connections_manager local_ucm(config_reader.get_local_port());
    udp_connections_manager ucm;

    //establishes the connection to the central server
    //does not return until both clients are connected to the server
    int server_peer_id;
    establish_connection_to_server(ucm, config_reader, server_peer_id);

    //register a lambda which routes the message received from the central client to the local peer
    ucm.start_peer_message_loop(server_peer_id, [&](const std::string &message) {
        local_ucm.send_message_to_all(message);
    });

    //connect to the local client by receiving an expected message from it (this message is also set in configuration)
    std::string expected_message = config_reader.get_connection_establishment_message();
    int local_id = local_ucm.add_new_peer(expected_message);

    //register a lambda which routes the message received from local client to the central server
    local_ucm.start_peer_message_loop(local_id, [&](const std::string &message) {
        ucm.send_message_to_peer(server_peer_id, message);
    });

    //make sure the application doesn't exit
    while (true)
    {
    }

    return 0;
}