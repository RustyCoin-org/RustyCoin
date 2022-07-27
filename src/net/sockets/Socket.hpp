#ifndef DEV_DYNAMO_SOCKET_H
#define DEV_DYNAMO_SOCKET_H

#include <net/common/lib_includes.hpp>
#include <net/common/IPVersion.hpp>
#include <net/common/Endpoint.hpp>
#include <net/common/NetTypes.hpp>
#include <net/common/NetConstants.hpp>
#include <net/common/SocketOptions.hpp>
#include <net/common/NetError.hpp>
#include <net/common/packet/Packet.hpp>

#include <iostream>
#include <assert.h>

namespace net
{
    class Socket
    {
    private:
        /* MEMBER VARIABLES */
        struct sockaddr_in address;

        IPVersion ip_version = IPVersion::IPv4;
        sock_t sock;

#ifdef _WIN32
        WSADATA wsa;
#endif

        /* MEMBER FUNCTIONS */
        ExitCode set_socket_option(SocketOption option, bool value);

    public:
        /* CONSTRUCTORS */
        Socket(int port, int domain = AF_INET, int service = SOCK_STREAM, int protocol = 0, ulong iface = INADDR_ANY);
        Socket(net::IPVersion = IPVersion::IPv4, sock_t handle = INVALID_SOCKET);

        /* VIRTUAL FUNCTIONS */
        // This function connects to the network using either bind() or connect() from winsock2.h
        virtual void sock_connect(int sock, struct sockaddr_in address) = 0;

        /* TESTERS */
        // This function exits the program if the connection is not properly established.
        // This should be checked frequently.
        static void test_connection(sock_t handle);

        /* GETTERS */
        struct sockaddr_in get_address();
        [[nodiscard]] sock_t get_socket_handle() const;

        /* SETTERS */
        ExitCode set_blocking(bool isBlocking);

        /* PUBLIC FUNCTIONS */
        static ExitCode r_send(sock_t socket_handle , const void* data, int numberOfBytes, int& bytesSent);
        static ExitCode r_recv(sock_t socket_handle, void* destination, int numberOfBytes, int& bytesReceived);
        static ExitCode r_sendAll(sock_t socket_handle, const void* data, int numberOfBytes);
        static ExitCode r_recvAll(sock_t socket_handle, void* destination, int numberOfBytes);
        static ExitCode r_send(sock_t socket_handle, Packet& packet);
        static ExitCode r_recv(sock_t socket_handle, Packet& packet);
    };
}

#endif //DEV_DYNAMO_SOCKET_H