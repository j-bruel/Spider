//
// Created by brd6 on 05/10/17.
//


#ifndef _RequestHandler_H_
# define _RequestHandler_H_

#include <unordered_map>
#include "Packet/Packet.hpp"
#include "Request.hpp"

namespace ts
{

  class Client;
  using PacketHandlerFunc = std::function<void(common::Packet const &packet)>;

  class RequestHandler
  {
   private:
    std::unordered_map<int, PacketHandlerFunc> mPacketHandlers;
    boost::shared_ptr<Client> mClient;

   public:
    explicit RequestHandler(boost::shared_ptr<Client> client);
    ~RequestHandler() = default;

    void handle(common::Packet const &packet);

   private:
    void initializeHandlers();
    void authenticateHandler(common::Packet const &packet);
    void clickActivityHandler(common::Packet const &packet);
    void keyInfoHandler(common::Packet const &packet);
    void pingReqHandler(common::Packet const &packet);

    void notifyRequestReceivedWithSuccess(unsigned int timestamp, int id);

  };
}

#endif /* !_RequestHandler_H_ */