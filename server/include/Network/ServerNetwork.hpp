//
// Created by brd6 on 27/09/17.
//


#ifndef _ServerNetwork_H_
# define _ServerNetwork_H_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <Client/ClientManager.hpp>
#include <DataRecorder/IDataRecorder.hpp>
#include "Client/Client.hpp"
#include "Socket/ServerSocket.hpp"

namespace ts
{
  class ServerNetwork
  {
   private:
    boost::asio::io_service mIos;
    common::tcp::ServerSocket mServerSocket;
    ClientManager mClientManager;
    std::shared_ptr<IDataRecorder> mDataRecorder;

   public:
    explicit ServerNetwork(std::string const &host, unsigned short port);
    ~ServerNetwork();

    //! Run the server
    void run();

    //! Stop the server
    void stop();

    //! Send a message to all clients
    //! \param msg
    void sendCommandToClients(std::string const &msg);

    //! Set the data record type
    //! \param type
    void setDataRecorder(std::string const &type, std::string const &path);

   private:
    //! Setup the accept for new client
    //! \param host
    //! \param port
    void setupAcceptor(std::string const &host, unsigned short port);

    //! Setup all callbacks for the network
    void setupCallbacks();

    //! Callback for new client accepted on the server
    //! \param client
    void onClientAccepted(ClientPtr client);

    //! Notify clients that the server is disconnected
    void notifyClientsServerDisconnect();
  };

}

#endif /* !_ServerNetwork_H_ */