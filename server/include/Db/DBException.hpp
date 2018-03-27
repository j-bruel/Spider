//!
//! \file DBException.hpp
//! \author jbruel
//! \date 03/10/2017
//!

#ifndef SPIDER_DBEXCEPTION_HPP
#define SPIDER_DBEXCEPTION_HPP

#include "SpiderException.hpp"

//!
//! \namespace Spider
//!
namespace Spider
{
	//!
	//! \class CoreException
	//! \brief Core exception class
	//!
	class DBException : public SpiderException
	{
	public:
		//!
		//! \brief Constructor of the default DBException class.
		//! \param msg Message related to the exception sent
		//!
		DBException(const std::string &msg) : SpiderException(msg) {}
		//!
		//! \brief Destructor of class DBException
		//!
		virtual ~DBException() throw() {}
	};
}

#endif //SPIDER_DBEXCEPTION_HPP
