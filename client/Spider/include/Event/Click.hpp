//!
//! \file IEvent.hpp
//! \author mliani
//! \date 30/09/2017
//!

#pragma once

#include "Event/IEvent.hpp"

//!
//! \namesapce Spider
//!
namespace Spider
{
//!
//! \namesapce Event
//!
namespace Event
{
	//!
	//! \class CLick
	//! \brief Handle click events
	//!
	class Click : public IEvent
	{
	private:
		ClickCoord	mPoint; //!< last coordonate of the mouse register 
		ClickType	mType; //!< type of the click register during the event (left, middle or right)

	public:
		//!
		//! \brief Constructor with a ClickType. Save the mouse position
		//! \param type is the type of the click (left, middle or right)
		//! \param activity is the last activity register
		//!
		Click(ClickType type, const std::string &activity);
		//!
		//! \brief Default copy constructor
		//!
		Click(const Click &) = delete;
		//!
		//! \brief Operator equal overlaod
		//! \return Event interface
		//!
		Click    &operator=(const Click &) = delete;
		//!
		//! \brief Default destroyer
		//!
		virtual ~Click() = default;

	public:
		//!
		//! \fn Extract Click Information
		//! \return Informations into string format
		//!
		virtual std::string getEventInfo() const;
		//!
		//! \brief Get id of the event
		//! \return Request ID
		//!
		virtual int getId() const { return (3);}
	};
}
}