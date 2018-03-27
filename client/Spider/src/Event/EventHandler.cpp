//!
//! \file EventHandler.cpp
//! \author jbruel
//! \date 03/10/2017
//!

#include <SDKDDKVer.h>
#include <iostream>
#include <sstream>
#include "Event/EventHandler.hpp"
#include "Event/Request.hpp"

namespace Spider
{
namespace Event
{	
	EventHandler::EventHandler(const std::string &host, unsigned short port) : mHandler(new DB::DBHandler),
                                                                               mClientSocket(mIos),
                                                                               mHost(host),
                                                                               mPort(port),
                                                                               mPacketManager(mClientSocket)
    {
		try {
			mHandler->connect(DBName);
			try {
				mClientSocket.connect(mHost, mPort);
				authConnexion();
			}
			catch (std::exception &) {}
        }
		catch (DBException &exception) {
			std::cerr << exception.what() << std::endl;
			mHandler = nullptr;
		}
	}

	bool	EventHandler::handle(const std::shared_ptr<IEvent> &event, const ssl::RSAKeys &rsa)
	{
		Event::Request	request;

		request.mFrom = "Spider-client";
		request.mTo = "Spider-server";
		request.mTimestamp = std::time(nullptr);
		request.mEvent = event;
		std::cout << request.generate(1, rsa, false) << std::endl;
		try {
			ReqHeader	header;

			header.id = htonl(event->getId());
			header.size = htonl(request.generate(event->getId(), rsa, false).size());
			mClientSocket.write(&header, sizeof(header));
			mClientSocket.write(request.generate(event->getId(), rsa, false).c_str(), request.generate(event->getId(), rsa, false).size());
        }
		catch (DBException &exception) {
			std::cerr << exception.what() << std::endl;
		}
		return (true);
	}

    void    EventHandler::authConnexion()
    {
		ReqHeader	header;

		header.id = htonl(1);
        std::stringstream	ssJson;

        ssJson << "{\"FROM\":\"Spider-client\",\"TO\":\"Spider-server\",\"TIMESTAMP\":\"" << std::time(nullptr) << "\",\"PUB_KEY\":\"\"}";
		header.size = htonl(ssJson.str().size());
		mClientSocket.write(&header, sizeof(header));
		mClientSocket.write(ssJson.str().c_str(), ssJson.str().size());
    }
}
}