//!
//! \file ClickAssociation.hpp
//! \author mliani
//! \date 30/09/2017
//!

#pragma once

#include <unordered_map>
#include "Event/IEvent.hpp"

namespace Spider
{
namespace Event
{
	std::unordered_map<int, Event::ClickType>	associativeClick{
		{ VK_LBUTTON, Event::LEFT_CLICK },
		{ VK_MBUTTON, Event::MIDDLE_CLICK },
		{ VK_RBUTTON, Event::RIGHT_CLICK }
	};
}
}