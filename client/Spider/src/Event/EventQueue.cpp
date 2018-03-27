//!
//! \file EventQueue.cpps
//! \author jbruel
//! \date 01/10/2017
//!

#include "Event/EventQueue.hpp"

namespace Spider
{
namespace Event
{
	void		EventQueue::push(IEvent *event)
	{
		mMutex.lock();
		mQueue.push_back(event);
		mMutex.unlock();
	}

	void		EventQueue::pop()
	{
		mMutex.lock();
		mQueue.erase(mQueue.begin());
		mMutex.unlock();
	}

	bool		EventQueue::get(std::shared_ptr<IEvent> &event)
	{
		mMutex.lock();
		if (!mIsSet || mQueue.size() <= 0)
		{
			mMutex.unlock();
			return (false);
		}
		event.reset(mQueue[0]);
		mMutex.unlock();
		return (true);
	}
}
}