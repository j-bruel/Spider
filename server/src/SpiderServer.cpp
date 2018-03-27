//
// Created by brd6 on 26/09/17.
//

#include "SpiderServer.hpp"

namespace ts
{
  SpiderServer::SpiderServer() :
  	mIsRunning(false)
  {
  }

  SpiderServer::~SpiderServer()
  {
    if (mCommandHandlerThread != nullptr &&
	mCommandHandlerThread->joinable())
      mCommandHandlerThread->join();
  }

  void SpiderServer::run()
  {
    initialize();

    mCommandHandlerThread = std::make_unique<std::thread>([=]() {
      handleCommands();
    });

    mServerNetwork->setDataRecorder(mRecordType, mFilePath);

    mServerNetwork->run();
  }

  void SpiderServer::quit()
  {
    mServerNetwork->stop();
    mIsRunning = false;
    std::cin.clear();
    std::fclose(stdin);
  }

  void SpiderServer::handleCommands()
  {
    while (mIsRunning)
      {
	auto command = parseCommand();

	if (mCommands.count(command.first) > 0)
	  mCommands[command.first](command.second);
	else
	  std::cerr << "Unknown command '" << command.first << "'" << std::endl;
      }
  }

  void SpiderServer::initialize()
  {
    mServerNetwork = std::make_unique<ServerNetwork>(mHost, mPort);

    initializeCommands();
    mIsRunning = true;
  }

  void SpiderServer::initializeCommands()
  {
    mCommands["help"] = [=](std::string const &) {
      showHelp();
    };

    mCommands["s::help"] = [=](std::string const &) {
      showServerHelp();
    };

    mCommands["s::quit"] = [=](std::string const &) {
      quit();
    };

    mCommands["c::send"] = [=](std::string const &arg) {
      sendCommandToClients(arg);
    };

  }

  void SpiderServer::showHelp()
  {
    std::cout << "Usage: [s::|c::][command] [arg...]" << std::endl;
    std::cout << "s::\t prefix server command follow by the command et args. The command will be execute by the server directly." << std::endl;
    std::cout << "c::\t prefix client command follow by the command et args. The command will be sended to the client directly." << std::endl;
    std::cout << "command\t the command to send" << std::endl;
    std::cout << "arg\t the arguments of the command if needed" << std::endl;
    std::cout << "Example: s::help, s::quit, c::send" << std::endl;
  }

  std::pair<std::string, std::string> SpiderServer::parseCommand()
  {
    std::string line;
    std::string args;

    auto &is = std::getline(std::cin, line);

    auto spacePos = line.find_first_of(' ');

    if (spacePos == std::string::npos)
      return {line, ""};

    if (!is || std::cin.eof())
      line = "s::quit";

    return {line.substr(0, spacePos), line.substr(spacePos + 1)};
  }

  void SpiderServer::setPort(unsigned short port)
  {
    mPort = port;
  }

  void SpiderServer::setFilePath(std::string const &filePath)
  {
    mFilePath = filePath;
  }

  void SpiderServer::setRecordType(std::string const &recordType)
  {
    mRecordType = recordType;
  }

  void SpiderServer::sendCommandToClients(std::string const &msg)
  {
    std::cout << "Send message to clients" << std::endl;
    mServerNetwork->sendCommandToClients(msg);
  }

  void SpiderServer::showServerHelp()
  {
    std::cout << "Usage: s::[command] [arg...]" << std::endl;
    std::cout << "command:\t the command to send" << std::endl;
    std::cout << "Available:\t s::help, s::quit" << std::endl;
  }

  void SpiderServer::setHost(const std::string &host)
  {
    mHost = host;
  }
}
