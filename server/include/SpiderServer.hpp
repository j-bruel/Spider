//
// Created by brd6 on 26/09/17.
//

#ifndef _SpiderServer_H_
#define _SpiderServer_H_

#include <bits/unique_ptr.h>
#include <vector>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <mutex>
#include "Util/Singleton.hpp"
#include "Client/Client.hpp"
#include "Util/Singleton.hpp"
#include "Network/ServerNetwork.hpp"

namespace ts
{
  using CommandFunc = std::function<void (std::string const &args)>;

  const std::string DEFAULT_HOST = "";
  const std::string DEFAULT_RECORD_TYPE = "sqlite";
  const std::string DEFAULT_FILE_PATH = "data/spider.sqlite";
  const unsigned short DEFAULT_PORT = 4242;

  class SpiderServer :
	  public common::Singleton<SpiderServer>
  {
   private:
    std::unique_ptr<std::thread> mCommandHandlerThread;
    bool mIsRunning;
    std::unordered_map<std::string, CommandFunc> mCommands;
    std::unique_ptr<ServerNetwork> mServerNetwork;
    unsigned short mPort;
    std::string mFilePath;
    std::string mRecordType;
    std::string mHost;

   public:
    SpiderServer();
    ~SpiderServer() override;

    //! Run the spider server
    void run();

    //! Quit the spider server
    void quit();

    //! Set the port
    //! \param port
    void setPort(unsigned short port);

    //! Set the file path for the data recording
    //! \param filePath
    void setFilePath(std::string const &filePath);

    //! Set the type of data recording
    //! \param recordType
    void setRecordType(std::string const &recordType);

    //! Set the host
    //! \param host
    void setHost(std::string const &host);

    //! Return info about the spider server
    //! \return
    std::string getInfo();

   private:
    //!
    //! Handle command line
    void handleCommands();

    //! Parse the command line
    //! \return command line info
    std::pair<std::string, std::string> parseCommand();

    //! Initialize the spider server
    void initialize();

    //! Initialize the commands accepted by the spider server
    void initializeCommands();

    //! show the general help about commands
    void showHelp();

    //! Send a command to clients
    //! \param msg
    void sendCommandToClients(std::string const &msg);

    //! Show the server command line help
    void showServerHelp();

  };

}
#endif //_SpiderServer_H_
