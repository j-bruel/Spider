//!
//! \file KeyReader.hpp
//! \author mliani
//! \date 30/09/2017
//!

#pragma once

#include <string>
#include <vector>
#include "Event/IEvent.hpp"
#include <windows.h>

//!
//! \namesapce Spider
//!
namespace Spider
{
//!
//! \namespace Core
//!
namespace Core
{
	const int IsTheTouch = -32767; //!< Value use by the function GetAsyncKey() to verify if a key is pressed

	const std::vector<int> mIgnoredChar({
		VK_RCONTROL,
		VK_LCONTROL,
		VK_LMENU,
		VK_RSHIFT,
		VK_LSHIFT
	}); //!< Key to ignored

	//!
	//! \class KeyReader
	//! \brief Read event
	//!
	class KeyReader
	{
	public:
		//!
		//! \brief Constructor
		//!
		KeyReader() : mSaveX(0), mSaveY(0) {};
		//!
		//! \brief Default copy constructor
		//!
		KeyReader(const KeyReader &) = delete;
		//!
		//! \brief Operator equal overlaod
		//! \return KeyReader
		//!
		KeyReader	&operator=(const KeyReader &) const = delete;
		//!
		//! \brief Default destroyer
		//!
		~KeyReader() = default;

	private:
		int				mSaveX; //!< previous mouse pos in x register
		int				mSaveY; //!< previous mouse pos in y register
		std::string 	mOld; //!< previous activity register
		std::string 	mActivity; //!< actual activity

	public:
		//!
		//! \brief Read Event and push it in the queue
		//! \param queue of IEvent
		//!
		void 	read(Event::EventQueue *queue);

	private:
		//!
		//! \brief find if the event catch is a click
		//! \param key to try
		//! \return NONE if it's not a click. Else the function return the ClickType
		//!
		Event::ClickType	isClick(int key);
		//!
		//! \brief find if the event catch is a mouse move
		//! \return NONE if it's not a click. Else the function return the ClickType
		//!
		Event::ClickType	isMouseMove();
		//!
		//! \brief verified if the key is a invalid key
		//! \param key to try
		//! \return return true if it's a key to ignored. Else, return false	
		//!
		bool				isInvalidKey(int key);
		//!
		//! \brief find the actual activity of the user
		//! \return Information into string format	
		//!
		std::string			findActivity();
	};
}
}
