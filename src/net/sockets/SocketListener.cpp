#include "SocketListener.hpp"

using namespace net;

/* CONSTRUCTOR */
SocketListener::SocketListener(int port, int backlog, int domain, int service, int protocol, ulong iface, int bklg) 
                : SocketBinder(port, domain, service, protocol, iface)
{
    backlog = bklg;
    r_listen();
    test_connection(listening);
}

/* PUBLIC FUNCTIONS */
void SocketListener::r_listen()
{
    listening = listen(get_socket_handle(), backlog);
}

/* GETTERS */
int SocketListener::get_backlog() const
{
    return backlog;
}

int SocketListener::get_listening() const
{
    return listening;
}