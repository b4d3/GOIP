#include <iostream>
#include <string>
#include <algorithm>
#include "../include/udp_connections_manager.h"
#include "../include/udp_service_provider.h"


int main() {
    
    goip::udp_connections_manager ucm;
    int server_peer_id = ucm.add_new_peer("52.14.208.77", 12346);
    std::string peer_ip;
    std::string peer_port;
    ucm.expect_single_message_from_peer(server_peer_id, [&](const std::string& message) {
        std::cout <<message << std::endl;
        peer_ip = message;
        });

    ucm.expect_single_message_from_peer(server_peer_id, [&](const std::string& message) {
        std::cout <<message << std::endl;
        peer_port = message;
        });

    int port_number = std::stoi(peer_port);
    peer_ip.erase(peer_ip.length()-1);
    std::cout <<"my peer is " << peer_ip << ":" << port_number << std::endl;
    
    int peer_id = ucm.add_new_peer(peer_ip, port_number);
    ucm.start_peer_message_loop(peer_id, [](const std::string& message){std::cout << message << std::endl;});

    long counter = 0;
    while(1) {
        if (counter%10000==0)
            ucm.send_message_to_peer(peer_id, "ivanova___poruka\n"); 
        counter++;
        }
    

    
    return 0;
}