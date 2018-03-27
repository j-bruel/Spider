//!
//! \file EventHandler.hpp
//! \author jbruel
//! \date 01/10/2017
//!

#pragma once
#include <memory>
#include "Event/IEvent.hpp"
#include "ssl/RSAKeys.hpp"
#include "Socket/TcpClientSocket.hpp"
#include "DB/DBHandler.hpp"
#include "Socket/PacketManager.hpp"
#include "Exception/DBException.hpp"
#include <boost/asio.hpp>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

//!
//! \namespace Spider
//!
namespace Spider
{
//!
//! \namespace Event
//!
namespace Event
{
	//!
	//! \class EventHandler
	//! \brief Handle events
	//!
	class EventHandler
	{
	private:
        boost::asio::io_service         mIos;
        ts::common::tcp::ClientSocket   mClientSocket;
        std::string                     mHost;
        unsigned short                  mPort;
        ts::common::PacketManager       mPacketManager;

	private:
        const std::string 	DBName = "Spider-Client.sqlite";

	private:
		struct	ReqHeader
		{
			uint32_t 	id;
			uint32_t 	size;
		};

	private:
		std::shared_ptr<DB::DBHandler>	mHandler; //!< Pointer on a Data Base handler

	public:
		//!
		//! \brief Default constructor
        //! \param host Host to connect
        //! \param port Port of the host
		//!
		EventHandler(const std::string &host, unsigned short port);
		//!
		//! \brief Default copy constructor
		//!
		EventHandler(const EventHandler &handler) = delete;
		//!
		//! \brief Equal operator overload
		//!
		EventHandler	&operator=(const EventHandler &handler) = delete;
		//!
		//! \brief Default destructor
		//!
		~EventHandler() { mClientSocket.close(); mHandler->disconnect(); }

	public:
		//!
		//! \brief Handle a event
		//! \param event Event to handle
		//! \return State of the method: Success or Failure
		//!
		bool	handle(const std::shared_ptr<IEvent> &event, const ssl::RSAKeys &rsa);

    private:
        void    authConnexion();
	};

}
}
