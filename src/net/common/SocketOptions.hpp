#ifndef SOCKET_OPTIONS_HPP
#define SOCKET_OPTIONS_HPP

namespace net
{
    enum SocketOption
    {
        TCP_NoDelay, // TRUE = Disable Nagle's algorithm.
        IPV6_Only    // TRUE = Only use IPv6.
    };
}

#endif