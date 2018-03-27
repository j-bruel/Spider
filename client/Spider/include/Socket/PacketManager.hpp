//
// Created by brd6 on 01/10/17.
//


#ifndef _PacketManager_H_
# define _PacketManager_H_

#include <functional>
#include "Socket/Packet.hpp"
#include "Socket/TcpClientSocket.hpp"

namespace ts
{
  namespace common
  {
    const int MAX_BODY_DATA_SIZE = 200000;

    using OnReadCompletePacket = std::function<void(Packet const &packet)>;
    using OnReadPacketError = std::function<void()>;

    using OnWriteCompletePacket = std::function<void()>;
    using OnWritePacketError = std::function<void()>;

    class PacketManager
    {
     private:
      common::tcp::ClientSocket &mClientSocket;
      OnReadCompletePacket mOnReadCompletePacket;
      OnReadPacketError mOnReadPacketError;
      OnWriteCompletePacket mOnWriteCompletePacket;
      OnWritePacketError mOnWritePacketError;
      std::shared_ptr<common::Packet> mPacketRead;
      std::shared_ptr<common::Packet> mPacketWrite;
      common::PacketQueue mPacketWritesQueue;

     public:
      explicit PacketManager(common::tcp::ClientSocket &clientSocket);
      ~PacketManager() = default;

      void asyncRead(OnReadCompletePacket onReadCompletePacket, OnReadPacketError onReadPacketError);
      void asyncWrite(std::shared_ptr<Packet> const &packet,
		      OnWriteCompletePacket onWriteCompletePacket,
		      OnWritePacketError onWritePacketError);

      void send(int packetHeaderId,
		std::string const &data,
		OnWriteCompletePacket onWriteCompletePacket,
		OnWritePacketError onWritePacketError);

     private:
      bool parseHeader(Packet &packet);

      bool isValidHeader(PacketHeader &header);

      void prepareHeaderSending(PacketHeader &header);
      void prepareHeaderReading(PacketHeader &header);

      void onReadPacketHeader(size_t size);
      void onReadPacketBody(size_t size);

      void onWritePacketHeader(size_t size);
      void onWritePacketBody(size_t size);

      void invokeOnReadError();
    };
  }
}

#endif /* !_PacketManager_H_ */