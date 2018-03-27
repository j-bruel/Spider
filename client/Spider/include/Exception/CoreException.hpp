//!
//! \file CoreException.hpp
//! \author jbruel
//! \date 26/09/2017
//!

#ifndef SPIDER_COREEXCEPTION_HPP
#define SPIDER_COREEXCEPTION_HPP

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
	class CoreException : public SpiderException
	{
	public:
		//!
		//! \brief Constructor of the default CoreException class.
		//! \param msg Message related to the exception sent
		//!
		CoreException(const std::string &msg) : SpiderException(msg) {}
		//!
		//! \brief Destructor of class CoreException
		//!
		virtual ~CoreException() throw() {}
	};
}

#endif //SPIDER_COREEXCEPTION_HPP
