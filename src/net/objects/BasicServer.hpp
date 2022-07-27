#ifndef BASIC_SERVER_HPP
#define BASIC_SERVER_HPP

#include <net/sockets/SocketListener.hpp>

namespace net
{
    class BasicServer
    {
    private:
        /* MEMBER VARIABLES */
        SocketListener* socket;

        /* VIRTUAL FUNCTIONS */
        virtual void acceptor() = 0;
        virtual void handler() = 0;
        virtual void responder() = 0;

    public:
        /* CONSTRUCTOR */
        BasicServer(int port, int backlog = 10, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY, int bklg = 10);
        
        /* VIRTUAL FUNCTIONS */
        virtual void launch() = 0;
        virtual void stop() = 0;

        /* GETTERS */
        SocketListener* get_socket();
    };
}

#endif