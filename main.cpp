/**
 * @file main.cpp
 * @author JoaoAJMatos (github.com/JoaoAJMatos)
 * @brief 
 * @version 0.1
 * @date 2022-07-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

#include <net/common/Endpoint.hpp>
#include <net/common/packet/Packet.hpp>

int main(void) 
{
    net::Packet p(net::PacketType::PT_Message);

    p << "Hello!";

    std::cout << "Packet size: " << p.getPacketSize() << std::endl;
    std::cout << "Packet type: " << p.getPacketType() << std::endl;

    net::Endpoint ep("google.com", 80);

    ep.print();

    return 0;
}