//
// Created by brd6 on 28/09/17.
//


#ifndef _UdpServerSocket_H_
# define _UdpServerSocket_H_

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include "Client/Client.hpp"
#include "UdpClientSocket.hpp"

namespace ts
{
  namespace common
  {
    namespace udp
    {
      class ServerSocket :
      	public ClientSocket
      {
       public:
	explicit ServerSocket(boost::asio::io_service &ios);

	void bind(std::string const &host, unsigned short port);

	/*
	 * Run the server
	 */
	void run();

	/**
	 * Stop the server
	 */
	void stop();

      };
    }
  }
}

#endif /* !_UdpServerSocket_H_ */