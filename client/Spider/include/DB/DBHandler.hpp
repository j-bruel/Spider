//!
//! \file DBHandler.hpp
//! \author aiacona
//! \date 03/10/2017
//!

#ifndef SPIDER_DB_DBHANDLER_HPP
#define SPIDER_DB_DBHANDLER_HPP

#include <sqlite3.h>
#include <memory>
#include <string>
#include "Event/Request.hpp"

//!
//! \namespace Spider
//!
namespace Spider
{
//!
//! \namespace DB
//!
namespace DB
{
	class DBHandler
	{
	private:
		const std::string	DropTable = "DROP TABLE IF EXISTS SpiderTable"; //!< SQL Command to drop the Spider table
		const std::string	Delete = "DELETE FROM SpiderTable WHERE TIMESTAMP = (SELECT MAX(TIMESTAMP) FROM SpiderTable);"; //!< SQL Command to delete (pop) the last information
		const std::string	Select = "SELECT * FROM SpiderTable;"; //!< SQL Command to select all data

	private:
		sqlite3	*mDb; //!< Pointer on a sqlite3 variable
		int		mRc; //!< Error handler

	public:
		//!
		//! \brief Default DBHandler constructor
		//!
		DBHandler() : mDb(nullptr), mRc(0) {}
		//!
		//! \brief Default copy constructor
		//!
		DBHandler(const DBHandler &) = delete;
		//!
		//! \brief Equal operator overload
		//!
		DBHandler	&operator=(const DBHandler &) = delete;
		//!
		//! \brief Default destructor
		//!
		~DBHandler() = default;

	public:
		//!
		//! \brief Connect fonction, create a data base
		//! \param name The name of the futur data base
		//!
		void		connect(const std::string &name);
		//!
		//! \brief Disconnect the instance of data base previously create
		//!
		inline void	disconnect() { sqlite3_close(mDb); }
		//!
		//! \brief Push a request in the data base
		//! \param request Request to push on the data base
		//!
		void		push(const Event::Request &request);
		//!
		//! \brief delete the last element of the data base
		//!
		void		pop();
		//!
		//! \brief Delete the spider table from the data base
		//!
		void		deleteTable();
		//!
		//! \brief Show all informations from the data base
		//!
		void		showTable();
	};
}
}

#endif //SPIDER_DB_DBHANDLER_HPP