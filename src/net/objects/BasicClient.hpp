#ifndef BASICCLIENT_HPP
#define BASICCLIENT_HPP

#include <net/sockets/SocketConnector.hpp>
#include <net/common/Endpoint.hpp>
#include <net/common/packet/Packet.hpp>

namespace net
{
    class BasicClient
    {
    private:
        SocketConnector* socket;

    public:
        /* CONSTRUCTOR */
        BasicClient(int port, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY);
        
        /* VIRTUAL FUNCTIONS */
        virtual char* request(const char* server_ip, const char* request) = 0;
        virtual char* request(Endpoint server_ep, Packet packet) = 0;
        
        /* GETTERS */
        SocketConnector* get_socket();
    };
}



#endif