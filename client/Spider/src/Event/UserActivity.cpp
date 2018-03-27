//!
//! \file UserActivity.hpp
//! \author mliani
//! \date 30/09/2017
//!

#include <windows.h>
#include <sstream>
#include <iostream>
#include "Event/UserActivity.hpp"

namespace Spider
{
namespace Event
{
	UserActivity::UserActivity(std::string activity) : IEvent(activity) {}

	std::string UserActivity::getEventInfo() const
	{
		return (std::string("\"PROCESS_INFO\":\"" + mProcessInfo + "\""));
	}
}
}