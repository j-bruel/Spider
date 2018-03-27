//
// Created by brd6 on 03/10/17.
//


#ifndef _ClientNetwork_H_
# define _ClientNetwork_H_

#include <boost/asio/io_service.hpp>
#include "Socket/ClientSocket.hpp"
#include "Packet/PacketManager.hpp"
#include "Request/RequestManager.hpp"

namespace ts
{
  class ClientNetwork
  {
   private:
    boost::asio::io_service mIos;
    common::tcp::ClientSocket mClientSocket;
    std::string mHost;
    unsigned short mPort;
    common::RequestManager mRequestManager;
    common::PacketManager mPacketManager;

   public:
    explicit ClientNetwork(std::string const &host, unsigned short port);
    ~ClientNetwork();

    /*
     * Run the client
     */
    void run();

    /**
     * Stop the client
     */
    void stop();

    void sendDataExample();

    void sendDataEasilyExample();
  };
}

#endif /* !_ClientNetwork_H_ */