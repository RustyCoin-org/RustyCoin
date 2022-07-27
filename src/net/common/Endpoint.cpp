#include "Endpoint.hpp"

/**
 * @brief Construct a new net::Endpoint::Endpoint object from an IP/hostname and port number. 
 * 
 * @param ip 
 * @param port 
 */
net::Endpoint::Endpoint(const char* ip, unsigned short port)
{
    this->port = port;

    /* IPv4 */
    in_addr addr; // Location to store the ipv4 address
    int res = inet_pton(AF_INET, ip, &addr);

    if (res == 1)
    {
        if (addr.s_addr != INADDR_NONE)
        {
            ip_string = ip;
            hostname = ip;

            ip_bytes.resize(sizeof(ulong));
            memcpy(&ip_bytes[0], &addr.s_addr, 4);

            ip_version = IPVersion::IPv4;
            return;
        }
    }

    // Attempt to resolve the hostname to Ipv4 address
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    addrinfo* hostinfo = nullptr;
    res = getaddrinfo(ip, NULL, &hints, &hostinfo);

    if (res == 0)
    {
        sockaddr_in* host_addr = reinterpret_cast<sockaddr_in*>(hostinfo->ai_addr);

        ip_string.resize(16);
        inet_ntop(AF_INET, &host_addr->sin_addr, &ip_string[0], 16);

        hostname = ip;

        ulong ip_long = host_addr->sin_addr.s_addr; // Get the IP address as unsigned long
        ip_bytes.resize(sizeof(ulong) - 4);
        memcpy(&ip_bytes[0], &ip_long, 4);   // Copy the bytes to our IP bytes vector

        ip_version = IPVersion::IPv4;

        freeaddrinfo(hostinfo); // Memory cleanup from getaddrinfo()
        return;
    }

    /* IPv6 */
    in6_addr addr6; // Location to store the ipv6 address
	res = inet_pton(AF_INET6, ip, &addr6);

	if (res == 1)
	{
	    ip_string = ip;
		hostname = ip;
		util::string::trim(ip_string);
		util::string::trim(hostname);

		ip_bytes.resize(16);
		memcpy(&ip_bytes[0], &addr6.__in6_u, 16);

		ip_version = IPVersion::IPv6;
		return;
	}

	// Attempt to resolve hostname to ipv6 address
	addrinfo hintsv6 = {};
	hints.ai_family = AF_INET6; //ipv6 addresses only
	addrinfo* hostinfov6 = nullptr;
	res = getaddrinfo(ip, NULL, &hintsv6, &hostinfov6);

	if (res == 0)
	{
		sockaddr_in6 * host_addr = reinterpret_cast<sockaddr_in6*>(hostinfov6->ai_addr);

		ip_string.resize(46);
		inet_ntop(AF_INET6, &host_addr->sin6_addr, &ip_string[0], 46);

		hostname = ip;
		util::string::trim(ip_string);
		util::string::trim(hostname);

		ip_bytes.resize(16);
		memcpy(&ip_bytes[0], &host_addr->sin6_addr, 16);

		ip_version = IPVersion::IPv6;

		freeaddrinfo(hostinfov6);
		return;
	}
}

/**
 * @brief Construct a new net::Endpoint::Endpoint object from a sockaddr struct
 * 
 * @param addr 
 */
net::Endpoint::Endpoint(sockaddr* addr)
{
    assert(addr->sa_family == AF_INET || addr->sa_family == AF_INET6);
	
	if (addr->sa_family == AF_INET) //IPv4
	{
		sockaddr_in* addrv4 = reinterpret_cast<sockaddr_in*>(addr);
		ip_version = IPVersion::IPv4;
		port = ntohs(addrv4->sin_port);

		ip_bytes.resize(sizeof(ulong));
		memcpy(&ip_bytes[0], &addrv4->sin_addr, sizeof(ulong));
		
		ip_string.resize(16);
		inet_ntop(AF_INET, &addrv4->sin_addr, &ip_string[0], 16);
		
		hostname = ip_string;
	}
	else //IPv6
	{
		sockaddr_in6* addrv6 = reinterpret_cast<sockaddr_in6*>(addr);
		ip_version = IPVersion::IPv6;
		port = ntohs(addrv6->sin6_port);
		
		ip_bytes.resize(16);
		memcpy(&ip_bytes[0], &addrv6->sin6_addr, 16);
		
		ip_string.resize(46);
		inet_ntop(AF_INET6, &addrv6->sin6_addr, &ip_string[0], 46);
		
		hostname = ip_string;
	}

	util::string::trim(ip_string);
	util::string::trim(hostname);
}

/* PUBLIC FUNCTIONS */
void net::Endpoint::print()
{
	switch (ip_version)
	{
	case IPVersion::IPv4:
		std::cout << "IP Version: IPv4" << std::endl;
		break;
	
	case IPVersion::IPv6:
		std::cout << "IP Version: IPv6" << std::endl;
		break;
	
	default:
		std::cout << "IP Version: Unknown" << std::endl;
	}
	
	std::cout << "Hostname: " << hostname << std::endl;
	std::cout << "IP: " << ip_string << std::endl;
	std::cout << "Port: " << port << std::endl;
	std::cout << "IP bytes..." << std::endl;
	
	for (auto & digit : ip_bytes)
	{
		std::cout << (int)digit << std::endl;
	}
}

/* GETTERS */
net::IPVersion net::Endpoint::get_ip_version() const
{
	return ip_version;
}

std::vector<uint8_t> net::Endpoint::get_ip_bytes() const
{
	return ip_bytes;
}

std::string net::Endpoint::get_hostname() const
{
	return hostname;
}

std::string net::Endpoint::get_ip_string() const
{
	return ip_string;
}

unsigned short net::Endpoint::get_port() const
{
	return port;
}

sockaddr_in net::Endpoint::get_sockaddr_ipv4() const
{
	assert(ip_version == IPVersion::IPv4);
	sockaddr_in addr = {};
	addr.sin_family = AF_INET;
	memcpy(&addr.sin_addr, &ip_bytes[0], sizeof(ulong));
	addr.sin_port = htons(port);
	return addr;
}

sockaddr_in6 net::Endpoint::get_sockaddr_ipv6() const
{
	assert(ip_version == IPVersion::IPv6);
	sockaddr_in6 addr = {};
	addr.sin6_family = AF_INET6;
	memcpy(&addr.sin6_addr, &ip_bytes[0], 16);
	addr.sin6_port = htons(port);
	return addr;
}