#ifndef SOCKET_LISTENER_HPP
#define SOCKET_LISTENER_HPP

#include "SocketBinder.hpp"

namespace net
{
    class SocketListener : public SocketBinder
    {
    private:
        /* MEMBER VARIABLES */
        int backlog;
        int listening;
    
    public:
        /* CONSTRUCTOR */
        SocketListener(int port, int backlog = 10, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY, int bklg = 10);

        /* PUBLIC FUNCTIONS */
        void r_listen();

        /* GETTERS */
        [[nodiscard]] int get_backlog() const;
        [[nodiscard]] int get_listening() const;
    };
}

#endif