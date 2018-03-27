//
// Created by brd6 on 03/10/17.
//

#include "Request/PingReq.hpp"
#include "Packet/Packet.hpp"
#include "Request/AuthReq.hpp"
#include "Network/ClientNetwork.hpp"

namespace ts
{

  ClientNetwork::ClientNetwork(std::string const &host, unsigned short port):
	  mClientSocket(mIos),
	  mHost(host),
	  mPort(port),
	  mPacketManager(mClientSocket)
  {
  }

  ClientNetwork::~ClientNetwork()
  {
    stop();
  }

  void ClientNetwork::run()
  {
    startConnection();
    mClientSocket.run();
  }

  void ClientNetwork::stop()
  {
    mClientSocket.close();
  }

  void ClientNetwork::onConnect()
  {
    std::cout << "connection successful!" << std::endl;

//    processReadLoop();
    processReadLoopManually();
//    sendAuthReq();
    sendAuthReqManually();
  }

  void ClientNetwork::startConnection()
  {
    mClientSocket.asyncConnect(mHost, mPort, [=]() {
      onConnect();
    });
  }

  void ClientNetwork::sendAuthReq()
  {
    std::string pubKey("qsdsfdmsdlmdslf");
    auto authReq = mRequestManager.prepare<common::AuthReq>("127.0.0.1", "127.0.0.1", pubKey);

    mPacketManager.send(authReq.first.getId(),
			authReq.second,
			[=](){
			  std::cout << "Sended!" << std::endl;
			},
			[=](){
			  // send error
			}
    );
  }

  void ClientNetwork::sendAuthReqManually()
  {
    // prepare the request
    common::AuthReq authReq;
    authReq.timestamp = "12838483883";
    authReq.to = "127.0.0.1";
    authReq.from = "127.0.0.1";
    authReq.pubKey = "qsdsfdmsdlmdslf";

    // json transformation
    auto jsonRequest = authReq.toJson();
    auto data = jsonRequest.c_str();

    // encrypt the request
    auto encryptedJsonRequest = data; //encrypt(data);

    // prepare the packet
    common::Packet packet;
    packet.header.id = authReq.getId();
    packet.header.size = std::strlen(encryptedJsonRequest);

    packet.body.data = new char[packet.header.size + 1];
    std::strcpy(packet.body.data, encryptedJsonRequest);

    // save the size because, he going to be erased by the next data transmission
    auto dataSize = packet.header.size;

    // Set network data transmission
    packet.header.id = htonl(packet.header.id);
    packet.header.size = htonl(packet.header.size);

    std::cout << packet.body.data << std::endl;

    // send the header (first)
    mClientSocket.asyncWrite(&packet.header, sizeof(packet.header),
			     [=](size_t headerSizeSended) {

			       std::cout << "Header sended! " << headerSizeSended << std::endl;
			       std::cout << packet.body.data << std::endl;

			       // send Body (then)
			       mClientSocket.asyncWrite(packet.body.data, dataSize,
							[=](size_t bodySizeSended) {

							  std::cout << "body sended! " << std::endl;

							});
			     });
  }

  void ClientNetwork::processReadLoop()
  {
    mPacketManager.asyncRead(
	    [=](common::Packet const &packet){
	      handlePacketReceived(packet);
	      processReadLoop();
	    },
	    [=](){
	      // read error
	    });
  }

  void ClientNetwork::processReadLoopManually()
  {
    // read the header (first)
    mClientSocket.asyncRead(&mPacketRead.header, sizeof(mPacketRead.header), [=](size_t size) {

      // Set network data reception
      mPacketRead.header.id = ntohl(mPacketRead.header.id);
      mPacketRead.header.size = ntohl(mPacketRead.header.size);

      mPacketRead.body.data = new char[mPacketRead.header.size + 1];
      mPacketRead.body.data[mPacketRead.header.size] = 0;

      // read the body (then)
      mClientSocket.asyncRead(mPacketRead.body.data, mPacketRead.header.size, [=](size_t size1) {

	// handle packet received
	handlePacketReceived(mPacketRead);

	// re-run the read loop
	processReadLoopManually();
      });

    });

  }

  void ClientNetwork::handlePacketReceived(common::Packet const &packet)
  {
    std::cout << "YOUPI!" << std::endl;
    std::cout << "id: " << packet.header.id << std::endl;
    std::cout << "size: " << packet.header.size << std::endl;
    std::cout << packet.body.data << std::endl;
    std::cout << "/END YOUPI!" << std::endl;

    // now we can send others data once connected!
    std::cout << (packet.header.id == common::RequestId::AUTH_RESP) << std::endl;

  }
}
