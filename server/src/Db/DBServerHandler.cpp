//!
//! \file DBServerHandler.hpp
//! \author aiacona
//! \date 03/10/2017
//!

#include <iostream>
#include "Db/DBServerHandler.hpp"
#include "Db/DBException.hpp"

namespace Spider
{
namespace DB
{

	void	DBServerHandler::connect(const std::string &name)
	{
		char			*ErrorMsg = nullptr;
		std::string sql = "CREATE TABLE IF NOT EXISTS SpiderTable(" +
						std::string("ID INTEGER PRIMARY KEY AUTOINCREMENT,") +
						"SENDER        TEXT    NOT NULL," +
						"RECEIVER      TEXT    NOT NULL," +
						"TIMESTAMP     INT   NOT NULL," +
						"REQ_IDX		INT    NOT NULL," +
						"EVENT          TEXT    NOT NULL);";
		
		mRc = sqlite3_open(name.c_str(), &(mDb));
		if (mRc)
			throw DBException("Can't open database: " + std::string(sqlite3_errmsg(mDb)));
		mRc = sqlite3_exec(mDb, sql.c_str(), nullptr, nullptr, &ErrorMsg);
		if (mRc != SQLITE_OK)
		{
			std::string	err("SQL error: " + (ErrorMsg == nullptr) ? "" : ErrorMsg);
			sqlite3_free(ErrorMsg);
			throw DBException(err);
		}
	}

  void	DBServerHandler::push(ts::common::Request &request)
	{
		std::string	sql;
		char		*ErrorMsg = nullptr;

		sql = "INSERT INTO SpiderTable (SENDER, RECEIVER, TIMESTAMP, REQ_IDX, EVENT) VALUES ('" + request.from + "','" + request.to + "'," +
		  request.timestamp + ",'" + std::to_string(request.getId()) + "','" + request.toJson() + "');";
		mRc = sqlite3_exec(mDb, sql.c_str(), nullptr, nullptr, &ErrorMsg);
		if (mRc != SQLITE_OK)
		{
			std::string	err("SQL error: " + (ErrorMsg == nullptr) ? "" : ErrorMsg);
			sqlite3_free(ErrorMsg);
			throw DBException(err + sql);
		}
	}

	void	DBServerHandler::pop()
	{
		char		*ErrorMsg = nullptr;

		mRc = sqlite3_exec(mDb, Delete.c_str(), nullptr, nullptr, &ErrorMsg);
		if (mRc != SQLITE_OK)
		{
			std::string	err("SQL error: " + std::string(ErrorMsg));
			sqlite3_free(ErrorMsg);
			throw DBException(err);
		}
	}

	void	DBServerHandler::deleteTable()
	{
		char			*ErrorMsg = nullptr;

		mRc = sqlite3_exec(mDb, DropTable.c_str(), nullptr, nullptr, &ErrorMsg);
		if (mRc != SQLITE_OK)
		{
			std::string		err("SQL error: " + std::string(ErrorMsg));
			sqlite3_free(ErrorMsg);
			throw DBException(err);
		}
	}

	void	DBServerHandler::showTable()
	{
		char *ErrorMsg = nullptr;

		mRc = sqlite3_exec(mDb, Select.c_str(), nullptr, nullptr, &ErrorMsg);
		if (mRc != SQLITE_OK)
		{
			std::string	err("SQL error: " + std::string(ErrorMsg));
			sqlite3_free(ErrorMsg);
			throw DBException(err);
		}
	}
}
}
