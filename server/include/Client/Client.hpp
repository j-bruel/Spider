//
// Created by brd6 on 26/09/17.
//

#ifndef _Client_H_
#define _Client_H_

#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <unordered_map>
#include "DataRecorder/IDataRecorder.hpp"
#include "Request/RequestHandler.hpp"
#include "Request/RequestManager.hpp"
#include "Socket/TcpClientSocket.hpp"
#include "Packet/Packet.hpp"
#include "Packet/PacketManager.hpp"

namespace ts
{
  class Client :
	  public boost::enable_shared_from_this<Client>,
	  private boost::noncopyable
  {
   private:
    common::tcp::ClientSocket mSocket;
    common::Packet mPacket;
    std::string mPubKey;
    bool mIsFirstConnection;
    bool mIsAuthenticate;
    common::RequestManager mRequestManager;
    common::PacketManager mPacketManager;
    std::function<void(boost::shared_ptr<Client> client)> mOnStopClient;
    bool mIsStopped;
    std::shared_ptr<RequestHandler> mRequestHandler;
    friend class RequestHandler;
    std::shared_ptr<IDataRecorder> mDataRecorder;


   public:
    explicit Client(boost::asio::io_service& ios);

    //! Return the boost socket instance
    //! \return
    boost::asio::ip::tcp::socket &getSocket();

    //! Start the client
    void start();

    //! Stop the client
    void stop();

    //! Set the on stop client callback
    //! \param onStopClient
    void setOnStopClientCallback(std::function<void(boost::shared_ptr<Client> client)> onStopClient);

    //! Send command
    //! \param msg
    void sendCommand(std::string const &msg);

    //! Return info about the client
    //! \return
    std::string getInfo();

    //! Send a request to notify server disconnection
    void sendServerDisconnectRequest();

    //! Set the data recorder type
    //! \param dataRecorder
    void setDataRecorder(std::shared_ptr<IDataRecorder> dataRecorder);

   private:
    //! Callback when packet is completely readed
    //! \param packet
    void onReadCompletePacket(common::Packet const &packet);

    //! Read loop
    void processReadLoop();

    //! Handle packet readed
    //! \param packet
    void handleReadPacket(const common::Packet &packet);

    //! Notify client that request failed
    void notifyErrorInRequestReceived();
  };

  using ClientPtr = boost::shared_ptr<Client>;
  using OnStopClientFunc = std::function<void(boost::shared_ptr<Client> client)>;

  namespace helper
  {
    //! Helper for create new client
    //! \param io_service
    //! \return
    static ClientPtr createClient(boost::asio::io_service &io_service)
    {
      return boost::make_shared<Client>(io_service);
    }
  }
}

#endif //_Client_H_
