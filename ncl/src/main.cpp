#include <iostream>
#include <string>
#include <algorithm>
#include <udp_connections_manager.h>
#include <udp_service_provider.h>
#include <configuration_reader.h>

void helper_printer(const std::string& message) {
    std::cout << "Got the following message:\n\t" << message << std::endl;
}

int main() {
    goip::configuration_reader config_reader;
    config_reader.test_print();
    goip::udp_connections_manager ucm;
    int server_peer_id = ucm.add_new_peer(config_reader.get_central_server_ip_address(), config_reader.get_central_server_port());
    std::string server_message = "ERROR!";

    while (server_message != "Connection to peer established!") {
        ucm.expect_single_message_from_peer(server_peer_id, [&](const std::string& message) {
            std::cout <<message << std::endl;
            server_message = message;
            });
    }

    ucm.start_peer_message_loop(server_peer_id, helper_printer);

    std::string message_for_peer = "Hello!";
    ucm.send_message_to_peer(server_peer_id, message_for_peer);
        
    
    while(true) {
    }

    return 0;
}