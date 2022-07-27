#ifndef SOCKET_BINDER_HPP
#define SOCKET_BINDER_HPP

#include <net/sockets/Socket.hpp>

namespace net
{
    class SocketBinder : public Socket
    {
    private:
        /* MEMBER VARIABLES */
        int binding_status;     // 0 if the binding was successful

        /* MEMBER FUNCTIONS */
        void sock_connect(sock_t sock, struct sockaddr_in address) override;

    public:
        /* CONSTRUCTORS */
        SocketBinder(int port, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY);
        SocketBinder(IPVersion ip_version = IPVersion::IPv4, sock_t handle = INVALID_SOCKET);
    
        /* GETTERS */
        int get_binding_status() const;
    };
}

#endif