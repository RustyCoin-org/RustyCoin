#include "PacketManager.hpp"

using namespace net;

void PacketManager::clear() // Clear the packet queue
{
    packets = std::queue<std::shared_ptr<Packet>>{};
}

bool PacketManager::hasPendingPackets() // Check if packets are pending
{
    return !packets.empty();
}

void PacketManager::append(std::shared_ptr<Packet> p) // Add packet to queue
{
    packets.push(std::move(p));
}

std::shared_ptr<Packet> PacketManager::next() // Get packet from the front of the queue
{
    return packets.front();
}

void PacketManager::pop() // Remove packet from the front of the queue
{
    packets.pop();
}