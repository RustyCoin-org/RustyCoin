#include "BasicClient.hpp"

using namespace net;

/* CONSTRUCTOR */
BasicClient::BasicClient(int port, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY)
{
    socket = new SocketConnector(port, domain, service, protocol, iface);
}

/* GETTERS */
SocketConnector* BasicClient::get_socket()
{
    return socket;
}