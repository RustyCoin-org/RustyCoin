#include <net/common/NetConstants.hpp>
#include "Packet.hpp"

using namespace net;

    Packet::Packet(PacketType packetType)
	{
		clear();
		setPacketType(packetType);
	}

	uint16_t Packet::getPacketSize()
	{
		uint16_t * packetSize = reinterpret_cast<uint16_t*>(&buffer[0]);
		return static_cast<uint16_t>(ntohs(*packetSize));
	}

	PacketType Packet::getPacketType()
	{
		PacketType * packetTypePtr = reinterpret_cast<PacketType*>(&buffer[2]);
		return static_cast<PacketType>(ntohs(*packetTypePtr));
	}

	void Packet::setPacketSize(uint16_t size)
	{
		uint16_t * sizePtr = reinterpret_cast<uint16_t*>(&buffer[0]);
		*sizePtr = static_cast<uint16_t>(htons(size));
	}

	void Packet::setPacketType(PacketType packetType)
	{
		PacketType * packetTypePtr = reinterpret_cast<PacketType*>(&buffer[2]);
		*packetTypePtr = static_cast<PacketType>(htons(packetType));
	}

	void Packet::clear()
	{
		buffer.resize(sizeof(uint16_t) + sizeof(PacketType)); //Packet Size + Packet Type
		setPacketType(PacketType::PT_Invalid);
		setPacketSize(sizeof(PacketType)); //"packet size" first 2 bytes are not considered for the stored packet size
		extractionOffset = sizeof(uint16_t) + sizeof(PacketType); //skip buffer & packet type reserve
	}

	void Packet::append(const void * data, uint32_t size)
	{
		if ((buffer.size() + size) > MAX_PACKET_SIZE)
			throw PacketException("[Packet::Append(const void*, uint32_t)] - Packet size exceeded max packet size.");

		buffer.insert(buffer.end(), (char*)data, (char*)data + size);
		setPacketSize(buffer.size() - 2); //-2 since 2 bytes are reserved for the actual packet size variable
	}

	Packet & Packet::operator << (uint32_t data)
	{
		data = htonl(data);
		append(&data, sizeof(uint32_t));
		return *this;
	}

	Packet & Packet::operator >> (uint32_t & data)
	{
		if ((extractionOffset + sizeof(uint32_t)) > buffer.size())
			throw PacketException("[Packet::operator >>(uint32_t &)] - Extraction offset exceeded buffer size.");

		data = *reinterpret_cast<uint32_t*>(&buffer[extractionOffset]);
		data = ntohl(data);
		extractionOffset += sizeof(uint32_t);
		return *this;
	}
	Packet & Packet::operator<<(const std::string & data)
	{
		*this << (uint32_t)data.size();
		append(data.data(), data.size());
		return *this;
	}
	Packet & Packet::operator>>(std::string & data)
	{
		data.clear();

		uint32_t stringSize = 0;
		*this >> stringSize;

		if ((extractionOffset + stringSize) > buffer.size())
			throw PacketException("[Packet::operator >>(std::string &)] - Extraction offset exceeded buffer size.");

		data.resize(stringSize);
		data.assign(&buffer[extractionOffset], stringSize);
		extractionOffset += stringSize;
		return *this;
	}
