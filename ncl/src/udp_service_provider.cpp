#include "../include/udp_service_provider.h"
#include <array>
#include <iostream>

using namespace goip;

udp_service_provider::udp_service_provider(boost::asio::io_service* io_service, boost::asio::ip::udp::socket* socket,
                const std::string& peer_ipv4_address, int peer_port_number):
                io_service {io_service}, socket{socket}, 
                remote_endpoint{new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(peer_ipv4_address), peer_port_number)}, 
                loop_running {false} {
                    socket->connect(*remote_endpoint);
                    send_message_to_peer("");
                }

udp_service_provider::~udp_service_provider() {
    //to be added
}

void udp_service_provider::send_message_to_peer(const std::string& message) {
    socket->send_to(boost::asio::buffer(message), *remote_endpoint);
}

void udp_service_provider::expect_single_message(std::function<void(const std::string& message)>& callback_function) {
    std::array<char, 120> buffer;
    size_t len = socket->receive_from(boost::asio::buffer(buffer), *remote_endpoint);
    std::string message(buffer.data(), len);
    callback_function(message);
}

void udp_service_provider::expect_single_message_async(std::function<void(const std::string& message)>& callback) {
    //not implemented yet!
}

void udp_service_provider::start_input_message_loop(std::function<void(const std::string& message)>& callback_function) {
    loop_running = true;
    callback = callback_function;
    message_receiver_thread = new std::thread(std::bind(&udp_service_provider::infinite_message_loop, this));
}

void udp_service_provider::terminate_input_message_loop() {
    loop_running = false;
}

void udp_service_provider::infinite_message_loop() {
    std::array<char, 120> buffer;
    while (loop_running) {
        size_t len = socket->receive_from(boost::asio::buffer(buffer), *remote_endpoint);
        std::string message(buffer.data(), len);
        callback(message);
    }
}