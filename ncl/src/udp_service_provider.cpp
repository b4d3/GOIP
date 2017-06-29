#include <udp_service_provider.h>
#include <array>
#include <iostream>

using namespace goip;

udp_service_provider::udp_service_provider(boost::asio::io_service *io_service, boost::asio::ip::udp::socket *socket,
                                           const std::string &peer_ipv4_address, int peer_port_number) : io_service{io_service}, socket{socket},
                                                                                                         remote_endpoint{new boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(peer_ipv4_address), peer_port_number)},
                                                                                                         loop_running{false}
{
    boost::system::error_code ec;
    socket->connect(*remote_endpoint, ec);
    if (ec)
    {
        std::cout << "Can't connect to remote server, will terminate the application!" << std::endl;
        exit(1);
    }
    send_message_to_peer("");
}
udp_service_provider::udp_service_provider(boost::asio::io_service *io_service, boost::asio::ip::udp::socket *socket, std::string expected_message) : io_service{io_service}, socket{socket},
                                                                                                                                                      remote_endpoint{new boost::asio::ip::udp::endpoint()},
                                                                                                                                                      loop_running{false}
{

    std::cout << "Got to this point!!!" << std::endl;
    bool peer_found = false;

    while (!peer_found)
    {
        std::array<char, 1024> receive_buffer;
        std::cout << "Got here before the problem!" << std::endl;
        size_t len = socket->receive_from(boost::asio::buffer(receive_buffer), *remote_endpoint, 0);

        std::string temp_object(receive_buffer.data(), len);

        std::cout << "Got the following message while trying to bind with local peer: " << temp_object << std::endl;

        if (temp_object == expected_message)
        {
            peer_found = true;
            std::cout << "Found the peer!" << std::endl;
        }
    }
}

udp_service_provider::~udp_service_provider()
{
    terminate_input_message_loop();
    message_receiver_thread->join();
    delete message_receiver_thread;
    delete remote_endpoint;
    //socket and io_service don't belong to this class, they should get deleted somewhere else
}

void udp_service_provider::send_message_to_peer(const std::string &message)
{
    try
    {
        socket->send_to(boost::asio::buffer(message), *remote_endpoint);
    }

    catch (boost::system::system_error &error)
    {
        std::cout << "Error while trying to send the udp message, will terminate!" << std::endl;
        exit(1);
    }
}

void udp_service_provider::expect_single_message(std::function<void(const std::string &message)> &callback_function)
{
    try
    {
        std::array<char, 120> buffer;
        size_t len = socket->receive_from(boost::asio::buffer(buffer), *remote_endpoint);
        std::string message(buffer.data(), len);
        callback_function(message);
    }

    catch (boost::system::system_error &error)
    {
        std::cout << "Error while trying to receive a single message, will terminate" << std::endl;
        exit(1);
    }
}

void udp_service_provider::expect_single_message_async(std::function<void(const std::string &message)> &callback)
{
    //not implemented yet!
}

void udp_service_provider::start_input_message_loop(std::function<void(const std::string &message)> &callback_function)
{
    loop_running = true;
    callback = callback_function;
    message_receiver_thread = new std::thread(std::bind(&udp_service_provider::infinite_message_loop, this));
}

void udp_service_provider::terminate_input_message_loop()
{
    loop_running = false;
}

void udp_service_provider::infinite_message_loop()
{
    std::array<char, 120> buffer;
    while (loop_running)
    {
        try
        {
            size_t len = socket->receive(boost::asio::buffer(buffer));
            std::string message(buffer.data(), len);
            callback(message);
        }

        catch (boost::system::system_error &error)
        {
            std::cout << "Error in infinite message loop, will terminate" << std::endl;
            exit(1);
        }
    }
}