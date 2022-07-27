#ifndef NET_ERROR_HPP
#define NET_ERROR_HPP

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1

namespace net
{
    enum ExitCode
    {
        Success,
        GenericError
    };
}


#endif