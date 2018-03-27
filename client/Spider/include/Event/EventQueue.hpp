//!
//! \file EventQueue.hpp
//! \author jbruel
//! \date 30/09/2017
//!

#ifndef SPIDER_CORE_EVENTQUEUE_HPP
#define SPIDER_CORE_EVENTQUEUE_HPP

#include <mutex>
#include <vector>
#include "Event/IEvent.hpp"

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
	//! \class EventQueue
	//! \brief Queue system for Spider events
	//!
	class	EventQueue
	{
	private:
		std::mutex			mMutex; //!< Mutex to protect multi-threading use
		std::vector<IEvent *>	mQueue; //!< The queue of the EventQueue system
		bool                mIsSet; //!< Event indicator to know if the queue is initialized

	public:
		//!
		//! \brief Default EventQueue constructor
		//!
		EventQueue() : mIsSet(true) {}
		//!
		//! \brief Default Copy constructor
		//!
		EventQueue(const EventQueue &) = delete;
		//!
		//! \brief Equal operator overload
		//!
		EventQueue &operator=(const EventQueue &) = delete;
		//!
		//! \brief Default destructor
		//!
		~EventQueue() = default;

	public:
		//!
		//! \brief Check if the queue is set
		//! \return State of the method: Success or Failure
		//!
		inline bool	isSet() const { return (mIsSet); }
		//!
		//! \brief Change the setting status of the queue system
		//!
		inline void	changeStatus() { mIsSet = false; }
		//!
		//! \brief Push a event in the queue
		//! \param event Event to push on the queue
		//!
		void		push(IEvent *event);
		//!
		//! \brief Pop a event in the queue
		//! \param event Event to pop of the queue
		//!
		void		pop();
		//!
		//! \brief Extract the lastest event of the queue
		//! \param event Futur extract event
		//! \return State of the method: Success or Failure
		//!
		bool		get(std::shared_ptr<IEvent> &event);
	};
}
}

#endif //SPIDER_CORE_EVENTQUEUE_HPP