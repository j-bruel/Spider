//!
//! \file UserActivity.hpp
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
	//! \class UserActivity
	//! \brief UserActivity Handler
	//!
	class UserActivity : public IEvent
	{
	private:
		//!
		//! \brief activity saved
		//!
	public:
		//!
		//! \brief Constructor with the last activity catch
		//!
		UserActivity(std::string activity);
		//!
		//! \brief Default copy constructor
		//! \param last activity register
		//!
		UserActivity(const UserActivity &) = delete;
		//!
		//! \brief Operator equal overlaod
		//! \return UserActivity
		//!
		UserActivity	&operator=(const UserActivity &) = delete;
		//!
		//! \brief Default destroyer
		//!
		virtual ~UserActivity() = default;

	public:
		//!
		//! \brief Extract UserActivity information
		//! \return Informations into string format
		//!
		virtual std::string getEventInfo() const;
		//!
		//! \brief Get id of the event
		//! \return Request ID
		//!
		virtual int getId() const { return (0);}
	};
}
}