#ifndef PACKET_MANAGER_HPP
#define PACKET_MANAGER_HPP

#include <queue>
#include <memory> // shared ptr

#include "Packet.hpp"

namespace net
{
    enum PacketManagerTask
    {
        ProcessPacketSize,
        ProcessPacketContents
    };

    class PacketManager
    {
    private:
        std::queue<std::shared_ptr<Packet>> packets;
    
    public:
        /* PUBLIC FUNCTIONS */
        void clear();
        bool hasPendingPackets();
        void append(std::shared_ptr<Packet> p);
        std::shared_ptr<Packet> next();
        void pop();

        /* PUBLIC VARIABLES */
        uint16_t currentPacketSize = 0;
        int currentPacketExtractionOffset = 0;
        PacketManagerTask currentTask = PacketManagerTask::ProcessPacketSize;
    };
}

#endif