/**
 * @file Endpoint.hpp
 * @author JoaoAJMatos (github.com/JoaoAJMatos)
 * 
 * @brief The Endpoint class defines a network endpoint. It is used to define a network address and contains all the relevant information of that address.
 *        An Endpoint object can be passed into the Socket constructor to create a Socket object.
 * 
 * @version 0.1
 * @date 2022-07-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ENDPOINT_HPP
#define ENDPOINT_HPP

#include <vector>
#include <assert.h>
#include <cstring>
#include <iostream>

#include <net/common/IPVersion.hpp>
#include <net/common/NetTypes.hpp>

#include "lib_includes.hpp"

#include "../../util/string/RustyString.hpp"

namespace net
{
      class Endpoint
      {
      private:
            /* MEMBER VARIABLES */
            IPVersion ip_version = IPVersion::Unknown;
            std::string hostname = "";
            std::string ip_string = "";
            std::vector<uint8_t> ip_bytes;
            unsigned short port = 0;

      public:
            /* CONSTRUCTORS */
            Endpoint() {};
            Endpoint(const char* ip, unsigned short port);
            Endpoint(sockaddr* addr);

            /* PUBLIC FUNCTIONS */
            void print();

            /* GETTERS */
            IPVersion get_ip_version() const;
            std::string get_hostname() const;
            std::string get_ip_string() const;
            std::vector<uint8_t> get_ip_bytes() const;
            unsigned short get_port() const;
            sockaddr_in get_sockaddr_ipv4() const;
            sockaddr_in6 get_sockaddr_ipv6() const;
      };
}

#endif