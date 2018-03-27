#include <cstdlib>
#include <iostream>
#include <csignal>
#include <Packet/Packet.hpp>
#include <ProgramOption/ProgramOption.hpp>
#include "SpiderServer.hpp"

static void sig_kill_handler(int)
{
  ts::SpiderServer::getInstance().quit();
}

static void setupSignalsHandler()
{
  std::signal(SIGINT, sig_kill_handler);
  std::signal(SIGTERM, sig_kill_handler);
  std::signal(SIGQUIT, sig_kill_handler);
  std::signal(SIGPIPE, sig_kill_handler);
}

static void setupProgramOptions(ts::ProgramOption &programOption)
{
  ts::Option helpOption("Show this usage", "help", "h");

  ts::Option portOption("The server port. Default: 4242", "port", "p");
  portOption.setHasValue(true);

  ts::Option recordOption("The data record's type. Available: [sqlite]",
			  "record",
			  "r");
  recordOption.setHasValue(true);

  ts::Option fileOption("The file path of the database to record data.", "file", "f");
  fileOption.setHasValue(true);

  ts::Option hostOption("The server address", "address", "a");
  hostOption.setHasValue(true);

  programOption.addOption(helpOption);
  programOption.addOption<unsigned short>(portOption, ts::DEFAULT_PORT);
  programOption.addOption<std::string>(recordOption, ts::DEFAULT_RECORD_TYPE);
  programOption.addOption<std::string>(fileOption, ts::DEFAULT_FILE_PATH);
  programOption.addOption<std::string>(hostOption, ts::DEFAULT_HOST);
}

void checkHelpProgramOption(ts::ProgramOption &programOption)
{
  if (programOption.has("help", "h"))
    {
      programOption.printUsage();
      std::exit(EXIT_SUCCESS);
    }
}

int main(int ac, char const **av)
{
  ts::ProgramOption programOption(ac, av);

  setupSignalsHandler();
  setupProgramOptions(programOption);

  auto &spiderServer = ts::SpiderServer::getInstance();

  try
    {
      programOption.run();
      checkHelpProgramOption(programOption);

      spiderServer.setPort(programOption.get<unsigned short>("port", "p"));
      spiderServer.setFilePath(programOption.get<std::string>("file", "f"));
      spiderServer.setRecordType(programOption.get<std::string>("record", "r"));
      spiderServer.setHost(programOption.get<std::string>("address", "a"));

      spiderServer.run();
    }
  catch (std::exception &e)
    {
      std::cerr << "An error appended: " << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  return EXIT_SUCCESS;
}