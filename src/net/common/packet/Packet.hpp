#ifndef PACKET_HPP
#define PACKET_HPP

#include <vector>
#include <net/common/lib_includes.hpp>
#include <net/common/packet/PacketException.hpp>
#include <net/common/packet/PacketType.hpp>

namespace net
{
    class Packet
    {
    public:
        /* CONSTRUCTOR */
        Packet(PacketType type = PacketType::PT_Invalid);

        /* PUBLIC FUNCTIONS */
        uint16_t getPacketSize();
        PacketType getPacketType();

        void setPacketType(PacketType type);
        void setPacketSize(uint16_t size);

        void clear();
        void append(const void* data, uint32_t size);
        
        Packet& operator << (uint32_t data);
		Packet& operator >> (uint32_t & data);
        
        Packet& operator << (const std::string& data);
        Packet& operator >> (std::string& data);

        uint32_t extractionOffset = 0;
        std::vector<char> buffer;
    };
}

#endif