#include "BasicServer.hpp"

using namespace net;

/* CONSTRUCTOR */
BasicServer::BasicServer(int port, int backlog = 10, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY, int bklg = 10)
{
    socket = new SocketListener(port, backlog, domain, service, protocol, iface, backlog);
}

/* GETTERS */
SocketListener* BasicServer::get_socket()
{
    return socket;
}