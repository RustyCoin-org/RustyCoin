#ifndef PACKET_TYPE_HPP
#define PACKET_TYPE_HPP

#include <stdint.h>

namespace net
{
    enum PacketType : uint16_t
    {
        PT_Invalid,
        PT_Message,
        PT_IntegerArray,
        PT_Test
    };
}

#endif