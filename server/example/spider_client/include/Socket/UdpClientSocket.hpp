//
// Created by brd6 on 28/09/17.
//


#ifndef _UdpClientSocket_H_
# define _UdpClientSocket_H_

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace ts
{
  namespace common
  {
    namespace udp
    {
      using OnReceiveFromFunc = std::function<void(size_t ret)>;
      using OnSendToFunc = std::function<void(size_t ret)>;

      class ClientSocket
      {
       protected:
	boost::asio::io_service &mIos;
	boost::asio::ip::udp::socket mSocket;
	OnSendToFunc mOnSendTo;
	OnReceiveFromFunc mOnReceiveFrom;

       public:
	explicit ClientSocket(boost::asio::io_service &ios);
	virtual ~ClientSocket() = default;

	/**
	 * Close the Client connection
	 */
	void close();

	/**
	 * Return the Boost asio socket
	 * @return
	 */
	boost::asio::ip::udp::socket &getSocket();

	/**
	 * Send data
	 * @param host
	 * @param port
	 * @param data
	 * @param size
	 * @return
	 */
	size_t sendTo(const std::string &host,
		      unsigned short port,
		      void const *data,
		      size_t size);

	/**
	 * send data asynchronously
	 * @param data
	 * @param size
	 * @param onWrite
	 */
	void asyncSendTo(const std::string &host,
			 unsigned short port,
			 void const *data,
			 size_t size,
			 OnSendToFunc onSendTo = nullptr);

	/**
	 * receive data
	 * @param data
	 * @param size
	 * @return
	 */
	size_t receiveFrom(const std::string &host,
			   unsigned short port,
			   void *data,
			   size_t size);

	/**
	 * receive data asynchronously
	 * @param host
	 * @param port
	 * @param data
	 * @param size
	 * @param onReceiveFrom
	 */
	void asyncReceiveFrom(const std::string &host,
			      unsigned short port,
			      void *data,
			      size_t size,
			      OnReceiveFromFunc onReceiveFrom = nullptr);

	/**
	 * Set the callback for asyncReceiveFrom
	 * @see asyncReceiveFrom
	 * @param onReceiveFrom
	 */
	void setOnReceiveFromCallback(OnReceiveFromFunc onReceiveFrom);

	/**
	 * Set the callback for asyncSendTo
	 * @see asyncSendTo
	 * @param onReceiveFrom
	 */
	void setOnSendToCallback(OnSendToFunc onSendTo);

	/**
	 * Return the address
	 * @return
	 */
	std::string getAddress() const;
      };
    }
  }
}

#endif /* !_UdpClientSocket_H_ */