//
// Created by brd6 on 01/10/17.
//


#ifndef _PacketManager_H_
# define _PacketManager_H_

#include <functional>
#include "Packet.hpp"
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

      //! Read packet asynchronously
      //! \param onReadCompletePacket
      //! \param onReadPacketError
      void asyncRead(OnReadCompletePacket onReadCompletePacket, OnReadPacketError onReadPacketError);

      //! Write packet asynchronously
      //! \param packet
      //! \param onWriteCompletePacket
      //! \param onWritePacketError
      void asyncWrite(std::shared_ptr<Packet> const &packet,
		      OnWriteCompletePacket onWriteCompletePacket,
		      OnWritePacketError onWritePacketError);

      //! Helper for send packet easily
      //! \param packetHeaderId
      //! \param data
      //! \param onWriteCompletePacket
      //! \param onWritePacketError
      void send(int packetHeaderId,
		std::string const &data,
		OnWriteCompletePacket onWriteCompletePacket,
		OnWritePacketError onWritePacketError);

     private:
      //! Parse the packet header
      //! \param packet
      //! \return
      bool parseHeader(Packet &packet);

      //! Check header validity
      //! \param header
      //! \return
      bool isValidHeader(PacketHeader &header);

      //! Prepare the header before sending
      //! \param header
      void prepareHeaderSending(PacketHeader &header);

      //! Prepare the header before reading
      //! \param header
      void prepareHeaderReading(PacketHeader &header);

      //! Callback when packet header is read
      //! \param size
      void onReadPacketHeader(size_t size);

      //! Callback when packet body is read
      //! \param size
      void onReadPacketBody(size_t size);

      //! Callback when packet header is write
      //! \param size
      void onWritePacketHeader(size_t size);

      //! Callback when packet body is write
      //! \param size
      void onWritePacketBody(size_t size);

      //! Helper for call error callback
      void invokeOnReadError();
    };
  }
}

#endif /* !_PacketManager_H_ */