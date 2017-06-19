#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>

namespace goip {
    
    class configuration_reader {
        public:
            configuration_reader(std::string filename = "../../configuration/ncl_config.json");
            ~configuration_reader();
            
            //tcp support not added yet!
            //this is for the communication between this api and its user
            //not this api and central server
            bool use_tcp_locally();
            std::string get_central_server_ip_address();
            int get_central_server_port();
            int get_local_port();
            std::string get_connection_establishment_message();
            int get_udp_package_size();
            void print_configuration();

        private:
            std::string central_server_ip_address;
            std::string connection_establishment_string;
            bool use_tcp_locally_enabled;
            int central_server_port;
            int local_port;
            int udp_package_size;
    };
}