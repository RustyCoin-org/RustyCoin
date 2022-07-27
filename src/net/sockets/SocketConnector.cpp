#include "SocketConnector.hpp"

using namespace net;

/* CONSTRUCTOR */
SocketConnector::SocketConnector(int port, int domain, int service, int protocol, ulong iface) : Socket(port, domain, service, protocol, iface)
{
    sock_connect(get_socket_handle(), get_address());
    test_connection(connection);
}

/* VIRTUAL FUNCTION OVERRIDES */
void SocketConnector::sock_connect(sock_t sock, struct sockaddr_in address)
{
    connection = connect(sock, (struct sockaddr*)&address, sizeof(address));
}

/* GETTERS */
int SocketConnector::get_connection() const
{
    return connection;
}