#ifndef DEV_DYNAMO_SOCKET_H
#define DEV_DYNAMO_SOCKET_H

#include "common/lib_includes.hpp"

#include <iostream>

namespace net
{
    class Socket
    {
    private:
        /* MEMBER VARIABLES */
        // Once instantiated, sock contains the address of a socket object on the network.
        // This should be a non-negative number.
        int sock;

        // The address variable is a struct that contains information about the protocol,
        // type, and interface of a given socket. These parameters are specified and set in the constructor
        struct sockaddr_in address;

#ifdef _WIN32
        // Struct that contains information about the windows sockets implementation
        WSADATA wsa;
#endif

    public:
        /* CONSTRUCTOR */
        // A parameterized constructor is required to instantiate the class.
        Socket(int domain, int service, int protocol, int port, unsigned long iface);

        /* VIRTUAL FUNCTIONS */
        // This function connects to the network using either bind() or connect() from winsock2.h
        virtual void sock_connect(int sock, struct sockaddr_in address) = 0;

        /* TESTERS */
        // This function exits the program if the connection is not properly established.
        // This should be checked frequently.
        static void test_connection(unsigned long);

        /* GETTERS */
        struct sockaddr_in get_address();
        [[nodiscard]] int get_sock() const;
    };
}

#endif //DEV_DYNAMO_SOCKET_H