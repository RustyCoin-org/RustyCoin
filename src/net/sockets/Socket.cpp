#include "Socket.hpp"

using namespace net;

/* CONSTRUCTOR */
Socket::Socket(IPVersion ipversion, sock_t handle) : ip_version(ipversion), sock(handle)
{
    assert(ipversion == IPVersion::IPv4 || ipversion == IPVersion::IPv6);
}

Socket::Socket(int port, int domain, int service, int protocol, ulong iface)
{
    assert(domain == AF_INET || domain == AF_INET6);
    assert(service == SOCK_STREAM || service == SOCK_DGRAM);
    assert(protocol == IPPROTO_TCP || protocol == IPPROTO_UDP);
    assert(port >= 0 && port <= 65535);
    assert(iface >= 0 && iface <= 255);
    
    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(iface);

#ifdef _WIN32
    // Initialize Winsock
    WORD wVersionRequested = MAKEWORD(2, 2);
    int iResult = WSAStartup(wVersionRequested, &wsa);

    if (iResult != 0)
    {
        std::cout << "WSAStartup failed with error: " << WSAGetLastError() << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
    
    sock = socket(domain, service, protocol);
    test_connection(sock);
}

/* PUBLIC FUNCTIONS */
void Socket::test_connection(sock_t handle)
{
    #ifdef _WIN32
    // Confirms that either the socket or the connection have been properly established
    // If an error is found, show it and exit the program
    switch (item_to_test)
    {
        case WSANOTINITIALISED:
            perror("WSA not initialized");
            exit(EXIT_FAILURE);
        case WSAENETDOWN:
            perror("Network subsystem failed");
            exit(EXIT_FAILURE);
        case WSAEACCES:
            perror("Socket has no access permissions. Unable to bind a datagram socket to the broadcast address.\nTry enabling SO_BROADCAST in setsockopt.");
            exit(EXIT_FAILURE);
        case WSAEADDRINUSE:
            perror("Address in use. Only one usage of each socket address is permitted.");
            exit(EXIT_FAILURE);
        case WSAEADDRNOTAVAIL:
            perror("Address not valid in the current context. Address is not a valid local IP address on this machine.");
            exit(EXIT_FAILURE);
        case WSAEFAULT:
            perror("Invalid pointer address.");
            exit(EXIT_FAILURE);
        case WSAEINPROGRESS:
            perror("A blocking Windows Sockets call is in progress. Or the service provider is still processing a callback function.");
            exit(EXIT_FAILURE);
        case WSAEINVAL:
            perror("Invalid argument was supplied. Or the socket object is a listening socket.");
            exit(EXIT_FAILURE);
        case WSAENOBUFS:
            perror("Not enough ephemeral ports to allocate for the bind. Or no buffer space is available.");
            exit(EXIT_FAILURE);
        case WSAENOTSOCK:
            perror("Not a socket.");
            exit(EXIT_FAILURE);
        case WSAEAFNOSUPPORT:
            perror("An address with the specified family cannot be used with this socket.");
            exit(EXIT_FAILURE);
        case WSAECONNREFUSED:
            perror("An attempt to connect was forcefully rejected.");
            exit(EXIT_FAILURE);
        case WSAENETUNREACH:
            perror("A socket operation was attempted to an unreachable host.");
            exit(EXIT_FAILURE);
        case WSAETIMEDOUT:
            perror("An attempt to connect timed out without establishing a connection.");
            exit(EXIT_FAILURE);
        case WSAEWOULDBLOCK:
            perror("Socket marked as nonblocking. The connection cannot be completed immediately.");
            exit(EXIT_FAILURE);
        default:
            return;
    }
#endif
    // TODO: Introduce better error detecting for Linux
    if (handle < 0)
    {
        perror("Connection failed...");
        exit(EXIT_FAILURE);
    }
}

/* PUBLIC FUNCTIONS */
/**
 * @brief Sets the socket to blocking/nonblocking mode
 * 
 * @param isBlocking 
 * @return ExitCode 
 */
ExitCode Socket::set_blocking(bool isBlocking)
{
    ulong nonBlocking = 1;
    ulong blocking = 0;

#ifdef _WIN32
    int res = ioctlsocket(sock, FIONBIO, isBlocking ? &blocking : &nonBlocking);
#else
    int res = ioctl(sock, FIONBIO, isBlocking ? &blocking : &nonBlocking);
#endif

    if (res < 0)
    {
        perror("Failed to set socket to blocking/nonblocking");
        return ExitCode::GenericError;
    }

    return ExitCode::Success;
}

ExitCode Socket::r_send(sock_t socket_handle, const void* data, int numberOfBytes, int &bytesSent)
{
    bytesSent = send(socket_handle, (const char*)data, numberOfBytes, 0);

    if (bytesSent == SOCKET_ERROR)
    {
        perror("Failed to send data");
        return ExitCode::GenericError;
    }

    return ExitCode::Success;
}

ExitCode Socket::r_recv(sock_t socket_handle, void* data, int numberOfBytes, int &bytesReceived)
{
    bytesReceived = recv(socket_handle, (char*)data, numberOfBytes, 0);

    if (bytesReceived == 0)
    {
        perror("Connection gracefully closed");
        return ExitCode::GenericError;
    }

    if (bytesReceived == SOCKET_ERROR)
    {
        perror("Failed to receive data");
        return ExitCode::GenericError;
    }

    return ExitCode::Success;
}

ExitCode Socket::r_sendAll(sock_t socket_handle, const void* data, int numberOfBytes)
{
    int totalBytesSent = 0;

    while (totalBytesSent < numberOfBytes)
    {
        int bytesRemaining = numberOfBytes - totalBytesSent;
        int bytesSent = 0;

        char* bufferOffset = (char*)data + totalBytesSent;
        ExitCode res = r_send(socket_handle, bufferOffset, bytesRemaining, bytesSent);

        if (res != ExitCode::Success) return res;

        totalBytesSent += bytesSent;
    }

    return ExitCode::Success;
}

ExitCode Socket::r_recvAll(sock_t socket_handle, void* data, int numberOfBytes)
{
    int totalBytesReceived = 0;

    while (totalBytesReceived < numberOfBytes)
    {
        int bytesRemaining = numberOfBytes - totalBytesReceived;
        int bytesReceived = 0;

        char* bufferOffset = (char*)data + totalBytesReceived;
        ExitCode res = r_recv(socket_handle, bufferOffset, bytesRemaining, bytesReceived);

        if (res != ExitCode::Success) return res;

        totalBytesReceived += bytesReceived;
    }

    return ExitCode::Success;
}

ExitCode Socket::r_send(sock_t socket_handle, Packet& packet)
{
    // First send the size of the packet
    uint16_t encodedPacketSize = htons(packet.buffer.size());
    ExitCode res = r_sendAll(socket_handle, &encodedPacketSize, sizeof(uint16_t));
    if (res != ExitCode::Success) return res;

    // Then send the packet data
    res = r_sendAll(socket_handle, packet.buffer.data(), packet.buffer.size());
    if (res != ExitCode::Success) return res;

    return ExitCode::Success;
}

ExitCode Socket::r_recv(sock_t socket_handle, Packet& packet)
{
    packet.clear();

    // First receive the size of the packet
    uint16_t encodedSize = 0;
    ExitCode res = r_recvAll(socket_handle, &encodedSize, sizeof(uint16_t));
    if (res != ExitCode::Success) return res;

    uint16_t bufferSize = ntohs(encodedSize);

    if (bufferSize > MAX_PACKET_SIZE) return ExitCode::GenericError; // Prevent buffer overflow

    // Then receive the packet data
    packet.buffer.resize(bufferSize);
    res = r_recvAll(socket_handle, &packet.buffer[0], bufferSize);
    if (res != ExitCode::Success) return res;

    return ExitCode::Success;
}

/* GETTRERS */
struct sockaddr_in Socket::get_address()
{
    return address;
}

sock_t Socket::get_socket_handle() const
{
    return sock;
}