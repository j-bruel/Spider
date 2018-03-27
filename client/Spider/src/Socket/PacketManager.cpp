//
// Created by brd6 on 01/10/17.
//

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <boost/asio.hpp>
#include "Socket/PacketManager.hpp"

namespace ts
{
  common::PacketManager::PacketManager(common::tcp::ClientSocket &clientSocket) :
	  mClientSocket(clientSocket)
  {
    mPacketRead = std::make_shared<common::Packet>();
    mPacketWrite = std::make_shared<common::Packet>();
  }

  bool common::PacketManager::parseHeader(common::Packet &packet)
  {
    if (!PacketManager::isValidHeader(packet.header))
      return false;

    packet.body.data = new char[packet.header.size + 1];
    packet.body.data[packet.header.size] = 0;

    return true;
  }

  bool common::PacketManager::isValidHeader(common::PacketHeader &header)
  {
    return (header.id >= 0 && header.size > 0 && header.size < MAX_BODY_DATA_SIZE);
  }

  void common::PacketManager::prepareHeaderSending(common::PacketHeader &header)
  {
    header.id = htonl(header.id);
    header.size = htonl(header.size);
  }

  void common::PacketManager::prepareHeaderReading(common::PacketHeader &header)
  {
    header.id = ntohl(header.id);
    header.size = ntohl(header.size);
  }

  void common::PacketManager::asyncRead(common::OnReadCompletePacket onReadCompletePacket,
				       common::OnReadPacketError onReadPacketError)
  {
    mOnReadCompletePacket = onReadCompletePacket;
    mOnReadPacketError = onReadPacketError;

    mClientSocket.asyncRead(&mPacketRead->header, sizeof(mPacketRead->header), [=](size_t size) {
      onReadPacketHeader(size);
    });
  }

  void common::PacketManager::onReadPacketHeader(size_t size)
  {
    prepareHeaderReading(mPacketRead->header);

    if (size != sizeof(mPacketRead->header) || !parseHeader(*mPacketRead))
      {
	invokeOnReadError();
	return;
      }

    mClientSocket.asyncRead(mPacketRead->body.data, mPacketRead->header.size, [=](size_t size1) {
      onReadPacketBody(size1);
    });
  }

  void common::PacketManager::onReadPacketBody(size_t size)
  {
    if (size != mPacketRead->header.size)
      {
	invokeOnReadError();
	return;
      }
    mOnReadCompletePacket(*mPacketRead);
  }

  void common::PacketManager::asyncWrite(std::shared_ptr<Packet> const &packet,
					 common::OnWriteCompletePacket onWriteCompletePacket,
					 common::OnWritePacketError onWritePacketError)
  {
    if (!isValidHeader(packet->header))
      {
	onWritePacketError();
	return;
      }

    bool writeInProgress = !mPacketWritesQueue.empty();
    mPacketWritesQueue.push_back(packet);

    if (writeInProgress)
      return;

    mPacketWrite = mPacketWritesQueue.front();

    prepareHeaderSending(mPacketWrite->header);

    mOnWriteCompletePacket = onWriteCompletePacket;
    mOnWritePacketError = onWritePacketError;

    mClientSocket.asyncWrite(&mPacketWrite->header, sizeof(mPacketWrite->header), [=](size_t size) {
      onWritePacketHeader(size);
    });
  }

  void common::PacketManager::onWritePacketHeader(size_t size)
  {
    if (size != sizeof(mPacketWrite->header))
      {
	mOnWritePacketError();
	return;
      }

    prepareHeaderReading(mPacketWrite->header);

    mClientSocket.asyncWrite(mPacketWrite->body.data, mPacketWrite->header.size, [=](size_t size1) {
      onWritePacketBody(size1);
    });
  }

  void common::PacketManager::onWritePacketBody(size_t size)
  {
    if (size != mPacketWrite->header.size)
      {
	mOnWritePacketError();
	return;
      }

    mPacketWritesQueue.pop_front();

    if (!mPacketWritesQueue.empty())
      asyncWrite(mPacketWritesQueue.front(), mOnWriteCompletePacket, mOnWritePacketError);

    mOnWriteCompletePacket();
  }

  void common::PacketManager::send(int packetHeaderId,
				   std::string const &data,
				   common::OnWriteCompletePacket onWriteCompletePacket,
				   common::OnWritePacketError onWritePacketError)
  {
    auto packet = std::make_shared<common::Packet>();

    packet->header.id = packetHeaderId;
    packet->header.size = static_cast<int>(data.size());
    packet->body.data = new char[data.size() + 1];
    packet->body.data[data.size()] = 0;

    std::strcpy(packet->body.data, data.c_str());

    asyncWrite(packet,
	       [=](){
		 onWriteCompletePacket();
	       },
	       [=](){
		 onWritePacketError();
	       });
  }

  void common::PacketManager::invokeOnReadError()
  {
    mPacketRead->header.reset();
    mPacketRead->body.reset();

    mOnReadPacketError();
  }

}