#include <iostream>
#include <string>
#include <algorithm>
#include <udp_connections_manager.h>
#include <udp_service_provider.h>
#include <configuration_reader.h>
#include <utils.h>

int main()
{

    goip::configuration_reader config_reader;
    config_reader.print_configuration();
    goip::udp_connections_manager local_ucm(config_reader.get_local_port());
    goip::udp_connections_manager ucm;

    //establishes the connection to the main server
    //does not return until both clients are connected to the server
    int server_peer_id;
    establish_connection_to_server(ucm, config_reader, server_peer_id);
    ucm.start_peer_message_loop(server_peer_id, [&](const std::string &message) {
        std::cout << "In the callback!" << std::endl;
        local_ucm.send_message_to_all(message);
    });

    //allows the local client to connect, this client will get all the messages
    //from the central server
    std::string expected_message = config_reader.get_connection_establishment_message();
    int local_id = local_ucm.add_new_peer(expected_message);

    //sends the message to the main server (which then routes it to the other client)
    std::string message_for_peer = "Hello!";
    ucm.send_message_to_peer(server_peer_id, message_for_peer);

    for (int i = 0; i < 10; i++)
    {
        std::cout << "Sending a message to remote peer!" << std::endl;
        ucm.send_message_to_peer(server_peer_id, message_for_peer);
    }

    while (true)
    {
    }

    return 0;
}