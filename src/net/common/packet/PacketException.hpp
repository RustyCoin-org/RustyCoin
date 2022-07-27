#ifndef PACKETEXCEPTION_HPP
#define PACKETEXCEPTION_HPP

#include <string>

namespace net
{
    class PacketException
    {
    private:
        std::string exception;
    
    public:
        /* CONSTRUCTOR */
        PacketException(std::string exception) : exception(exception) {}
        
        /* PUBLIC FUNCTIONS */
        const char* what()
        {
            return exception.c_str();
        }

        std::string toString()
        {
            return exception;
        }
    };
}

#endif