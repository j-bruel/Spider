//!
//! \file IEvent.hpp
//! \author mliani
//! \date 30/09/2017
//!

#pragma once

#include <string>

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
		//! \enum ClickType
		//! \brief Define the type of the click from the user
		//!
		enum ClickType
		{
			LEFT_CLICK,
			MIDDLE_CLICK,
			RIGHT_CLICK,
			NONE
		};

		//!
		//! \struct ClickCoord
		//! \brief Define the click coordonate
		//!
		struct ClickCoord
		{
			int pX;
			int pY;
		};
		//!
		//! \class IEvent
		//! \brief Event interface
		//!
		class IEvent
		{
		protected:
			std::string mProcessInfo; //!< actual process register

		public:
			//!
			//! \brief Default constructor
			//! \param last activity register
			//!
			IEvent(const std::string &activity) : mProcessInfo(activity) {};
			//!
			//! \brief Default copy constructor
			//!
			IEvent(const IEvent &) = delete;
			//!
			//! \brief Operator equal overlaod
			//! \return Event interface
			//!
			IEvent	&operator=(const IEvent &) = delete;
			//!
			//! \brief Default destroyer
			//!
			virtual ~IEvent() = default;

		public:
			//!
			//! \brief Extract Event information
			//! \return Informations into string format
			//!
			virtual std::string	getEventInfo() const = 0;
			//!
			//! \brief Get id of the event
			//! \return Request ID
			//!
			virtual int getId() const = 0;
		};
	}
}