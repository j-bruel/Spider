//
// Created by brd6 on 27/09/17.
//

#include <iostream>
#include <utility>
#include <Request/Request.hpp>
#include <DataRecorder/SqliteDataRecorder.hpp>
#include "Network/ServerNetwork.hpp"
#include "Client/ClientManager.hpp"
#include "Util/Debug.hpp"

namespace ts
{

  ServerNetwork::ServerNetwork(const std::string &host, unsigned short port) :
	  mServerSocket(mIos)
  {
    setupAcceptor(host, port);
    setupCallbacks();
  }

  ServerNetwork::~ServerNetwork()
  {
    mClientManager.stopAll();
    mServerSocket.stop();
  }

  void ServerNetwork::setupAcceptor(std::string const &host, unsigned short port)
  {
    mServerSocket.bind(host, port);
    mServerSocket.enableReUseAddress();
    mServerSocket.listen();
  }

  void ServerNetwork::run()
  {
    LOG << "Server run. " << mServerSocket.getInfo() << std::endl;

    mServerSocket.asyncAccept();
    mServerSocket.run();
  }

  void ServerNetwork::stop()
  {
    notifyClientsServerDisconnect();
    mServerSocket.stop();
  }

  void ServerNetwork::onClientAccepted(ClientPtr client)
  {
    client->setOnStopClientCallback([=](ClientPtr c){

      LOG_WARN << c->getInfo() << " disconnected" << std::endl;

      mClientManager.remove(c);
    });

    client->start();
    client->setDataRecorder(mDataRecorder);

    mClientManager.add(client);

    LOG << "NEW CLIENT! at " << client->getInfo() << std::endl;
  }

  void ServerNetwork::setupCallbacks()
  {
    mServerSocket.setOnClientAcceptedCallback([=](ClientPtr client) {
      this->onClientAccepted(client);
    });
  }

  void ServerNetwork::sendCommandToClients(const std::string &msg)
  {
    mClientManager.foreach([=](ClientPtr client){
      client->sendCommand(msg);
    });
  }

  void ServerNetwork::notifyClientsServerDisconnect()
  {
    mClientManager.foreach([=](ClientPtr client){

      client->sendServerDisconnectRequest();
    });

  }

  void ServerNetwork::setDataRecorder(const std::string &type, std::string const &path)
  {
    mDataRecorder = std::make_shared<SqliteDataRecorder>();

    mDataRecorder->initialize(path);
  }

}

