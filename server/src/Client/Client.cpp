//
// Created by brd6 on 26/09/17.
//

#include <iostream>
#include <boost/make_shared.hpp>
#include <SpiderServer.hpp>
#include "Request/DisconnectReq.hpp"
#include "Request/ErrorReq.hpp"
#include "Request/NoticeReceiptReq.hpp"
#include "Request/PingResp.hpp"
#include "Request/PingReq.hpp"
#include "Request/KeyInfoReq.hpp"
#include "Request/ClickActivityReq.hpp"
#include "Request/CommandReq.hpp"
#include "Client/Client.hpp"
#include "Request/AuthReq.hpp"
#include "Request/AuthResp.hpp"
#include "Util/Debug.hpp"

namespace ts
{
  Client::Client(boost::asio::io_service& ios) :
	  mSocket(ios),
	  mIsAuthenticate(false),
	  mPacketManager(mSocket),
	  mOnStopClient(nullptr),
	  mIsStopped(false),
	  mIsFirstConnection(false)
  {
    mSocket.setOnDisconnectCallback(
	    [=]() {

	      stop();

	    });
  }

  void Client::start()
  {
    mRequestHandler = std::make_shared<RequestHandler>(shared_from_this());

    mIsFirstConnection = true;
    mSocket.forceConnectionStatusHas(true);
    processReadLoop();
  }

  void Client::stop()
  {
    if (mIsStopped)
      return;

    mSocket.close();

    mIsStopped = true;

    if (mOnStopClient != nullptr)
      mOnStopClient(shared_from_this());
  }

  boost::asio::ip::tcp::socket &Client::getSocket()
  {
    return mSocket.getSocket();
  }

  void Client::onReadCompletePacket(common::Packet const &packet)
  {
    if (mIsFirstConnection)
      {
	mRequestHandler->handle(packet);
      }
    else
      {
	if (!mIsAuthenticate)
	  {
	    stop();
	    return;
	  }
	handleReadPacket(packet);
      }

    processReadLoop();
  }

  void Client::processReadLoop()
  {
    mPacketManager.asyncRead(
	    [=](common::Packet const &packet){
	      onReadCompletePacket(packet);
	    },
	    [=](){
	      LOG_ERR << "Read error." << std::endl;

	      notifyErrorInRequestReceived();

	    });
  }

  void Client::setOnStopClientCallback(OnStopClientFunc onStopClient)
  {
    mOnStopClient = onStopClient;
  }

  void Client::sendCommand(std::string const &msg)
  {
    if (!mIsAuthenticate)
      {
	LOG_WARN << "Client isn't auth " << this->getInfo() << std::endl;
	return;
      }
    auto commandReq = mRequestManager.prepare<common::CommandReq>(
	    mSocket.getAddress(),
	    mSocket.getAddress(),
	    msg);

    mPacketManager.send(commandReq.first.getId(),
			commandReq.second,
			[=](){
			  // OK
			  LOG << "Write ok! CommandReq to " << this->getInfo() << std::endl;
			},
			[=](){
			  // KO
			  LOG_ERR << "Write error. CommandReq to " << this->getInfo() << std::endl;
			}
    );
  }

  void Client::handleReadPacket(const common::Packet &packet)
  {
    mRequestHandler->handle(packet);
  }

  std::string Client::getInfo()
  {
    return mSocket.getInfo();
  }

  void Client::notifyErrorInRequestReceived()
  {
    auto pingResp = mRequestManager.prepare<common::ErrorReq>(mSocket.getAddress(),
								      mSocket.getAddress(),
								      common::ErrorType::READ_ERROR,
								      "Error during read packet");
    mPacketManager.send(pingResp.first.getId(),
			pingResp.second,
			[=](){
			  LOG << "Write ok! ErrorReq to " << this->getInfo() << std::endl;
			},
			[=](){
			  LOG_ERR << "Write error! ErrorReq to " << this->getInfo() << std::endl;
			}
    );
  }

  void Client::sendServerDisconnectRequest()
  {
    if (!mIsAuthenticate)
      {
	LOG_WARN << "Client isn't auth " << this->getInfo() << std::endl;
	return;
      }

    auto request = mRequestManager.prepare<common::DisconnectReq>(mSocket.getAddress(), mSocket.getAddress());

    mPacketManager.send(request.first.getId(),
			request.second,
			[=](){
			  // OK
			  LOG << "Write ok! DisconnectReq to " << this->getInfo() << std::endl;
			},
			[=](){
			  // KO
			  LOG_ERR << "Write error. DisconnectReq to " << this->getInfo() << std::endl;
			}
    );
  }

  void Client::setDataRecorder(std::shared_ptr<IDataRecorder> dataRecorder)
  {
    mDataRecorder = dataRecorder;

    mDataRecorder->initialize(ts::DEFAULT_FILE_PATH);
  }

}
