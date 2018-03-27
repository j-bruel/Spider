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
    /**
     * Connection
     */

//     sync connect
//    mClientSocket.connect(mHost, mPort);
//    std::cout << "Connected!" << std::endl;

//     async connect
    mClientSocket.asyncConnect(mHost, mPort, [=]() {
      std::cout << "connection successful!" << std::endl;
      sendDataEasilyExample();
    });
    mClientSocket.run();

    /**
     * Send
     */

//    sendDataExample();
//    sendDataEasilyExample();
  }

  void ClientNetwork::stop()
  {
    mClientSocket.close();
  }

  void ClientNetwork::sendDataExample()
  {
    // prepare the request
    common::AuthReq authReq;

    // fill the request
    authReq.timestamp = "12838483883";
    authReq.to = "127.0.0.1";
    authReq.from = "127.0.0.1";
    authReq.pubKey = "qsdsfdmsdlmdslf";

    // json transformation
    auto jsonRequest = authReq.toJson();
    auto data = jsonRequest.c_str();

    std::cout << "JSON" << std::endl;
    std::cout << jsonRequest << std::endl;

    // encrypt the request
    auto encryptedJsonRequest = data; //encrypt(data);

    // prepare the packet
    common::Packet packet;

    // fill the packet
    packet.header.id = authReq.getId();
    packet.header.size = static_cast<int>(std::strlen(encryptedJsonRequest));
    packet.body.data = const_cast<char *>(encryptedJsonRequest);

    auto size = packet.header.size;

    // Set network data transmission
    packet.header.id = htonl(packet.header.id);
    packet.header.size = htonl(packet.header.size);

    // send the packet - Header
    // sync
    mClientSocket.write(&packet.header, sizeof(packet.header));
    // async
//    mClientSocket.asyncWrite(&packet.header, sizeof(packet.header), [=](size_t size) { std::cout << "Header sended!" << std::endl; });

    // send the packet - Body
    mClientSocket.write(packet.body.data, size);
    // async
//    mClientSocket.asyncWrite(packet.body.data, packet.header.size, [=](size_t size) { std::cout << "body sended!" << std::endl; });

    // send packet complete !
    std::cout << "send OKOKO" << std::endl;
    while (true);
  }

  void ClientNetwork::sendDataEasilyExample()
  {
    std::string pubKey("qsdsfdmsdlmdslf");

    auto authReq = mRequestManager.prepare<common::AuthReq>("127.0.0.1", "127.0.0.1", pubKey);

    std::cout << "ID: " << authReq.first.getId() << std::endl;
    std::cout << ">: " << authReq.second << std::endl;

    mPacketManager.send(authReq.first.getId(),
			authReq.second,
			[=](){
			  // OK
			  std::cout << "Sended!" << std::endl;

			  /////////////////////////////////////////

			  auto pingReq = mRequestManager.prepare<common::PingReq>("127.0.0.1", "127.0.0.1");

			  std::cout << "PING ID: " << pingReq.first.getId() << std::endl;
			  std::cout << ">: " << pingReq.second << std::endl;

			  mPacketManager.send(pingReq.first.getId(),
					      pingReq.second,
					      [=](){
						// OK
						std::cout << "Ping Sended!" << std::endl;
						while (true);
					      },
					      [=](){
						// KO
						std::cerr << "Error in data sending" << std::endl;
					      }
			  );

//			  while(true);

			},
			[=](){
			  // KO
			  std::cerr << "2 - Error in data sending" << std::endl;
			}
    );

  }
}
