//!
//! \file Click.cpp
//! \author mliani
//! \date 30/09/2017
//!

#include <windows.h>
#include <sstream>
#include "Event/Click.hpp"

namespace Spider
{
namespace Event
{
	Click::Click(ClickType type, const std::string &activity) : IEvent(activity)
	{
		POINT p;
		if (GetCursorPos(&p))
		{
			mPoint.pX = p.x;
			mPoint.pY = p.y;
		}
		mType = type;
	}

	std::string Click::getEventInfo() const
	{
		return (std::string("\"CLICK_TYPE\":" + std::to_string(mType) +
			",\"CLICK_X\":" + std::to_string(mPoint.pX) +
			",\"CLICK_Y\":" + std::to_string(mPoint.pY)) +
			",\"PROCESS_INFO\":\"" + mProcessInfo + "\"");
	}
	}
}