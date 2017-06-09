#include <configuration_reader.h>

using namespace goip;
using namespace boost::property_tree;

configuration_reader::configuration_reader(std::string filename) {
    ptree tree;
    read_json(filename, tree);
    local_port = tree.get<int>("ncl.local_udp_port");
    central_server_ip_address = tree.get<std::string>("ncl.central_server_information.ip_address");
    central_server_port = tree.get<int>("ncl.central_server_information.port");
    use_tcp_locally_enabled = tree.get<bool>("ncl.use_tcp_locally");
}

configuration_reader::~configuration_reader() {
    //tbi
}

bool configuration_reader::use_tcp_locally() {
    //hardcoded until tcp support is added
    return false;
}

std::string configuration_reader::get_central_server_ip_address() {
    return central_server_ip_address;
}

int configuration_reader::get_central_server_port() {
    return central_server_port;
}

int configuration_reader::get_local_port() {
    return local_port;
}

void configuration_reader::test_print() {
    std::cout <<"This is the configuration..." << std::endl;
    std::cout <<"Remote server ip address and port: " << central_server_ip_address << ":" << central_server_port << std::endl;
    std::cout <<"Use tcp locally: " << use_tcp_locally_enabled << std::endl;
    std::cout <<"Local port number: " << local_port << std::endl;
}