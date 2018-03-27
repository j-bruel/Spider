//
// Created by brd6 on 29/09/17.
//


#ifndef _Packet_H_
# define _Packet_H_

#include <memory>
#include <cstdint>
#include <deque>

namespace ts
{
  namespace common
  {
    struct PacketHeader
    {
      int id;
      int size;

      PacketHeader() : id(0), size(0) {}

      //! Reset data in header
      void reset()
      {
	id = 0;
	size = 0;
      }
    };

    struct PacketBody
    {
      char *data;

      PacketBody() : data(nullptr) {}

      //! Reset data in body
      void reset()
      {
	data = nullptr;
      }
    };

    struct Packet
    {
      PacketHeader header{};
      PacketBody body{};

      Packet()
      {
	header.reset();
	body.reset();
      }

    };

    using PacketQueue = std::deque<std::shared_ptr<Packet>>;
  }
}

#endif /* !_Packet_H_ */