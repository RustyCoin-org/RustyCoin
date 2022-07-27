#ifndef SOCKET_CONNECTOR_HPP
#define SOCKET_CONNECTOR_HPP

#include "Socket.hpp"

namespace net
{
    class SocketConnector : public Socket
    {
    private:
        /* MEMBER VARIABLES */
        int connection;         // 0 if the connection was successful

    public:
        /* CONSTRUCTOR */
        SocketConnector(int port, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY);

        /* VIRTUAL FUNCTION OVERRIDES */
        void sock_connect(sock_t sock, struct sockaddr_in address) override;

        /* GETTERS */
        [[nodiscard]] int get_connection() const;
    };
}

#endif