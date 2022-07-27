#include "SocketBinder.hpp"

using namespace net;

/* CONSTRUCTORS */
SocketBinder::SocketBinder(int port, int domain, int service, int protocol, ulong iface) : Socket(port, domain, service, protocol, iface)
{
    sock_connect(get_socket_handle(), get_address());
    test_connection(binding_status);
}

/* VIRTUAL FUNCTION OVERRIDES */
/**
 * @brief sock_connect() override from Socket.hpp
 * 
 * @details Binds a socket to an address
 * 
 * @param sock 
 * @param address 
 */
void SocketBinder::sock_connect(sock_t sock, struct sockaddr_in address)
{
    binding_status = bind(sock, (struct sockaddr*)&address, sizeof(address));
}

/* GETTERS */
int SocketBinder::get_binding_status() const
{
    return binding_status;
}