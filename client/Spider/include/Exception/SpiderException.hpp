//!
//! \file SpiderException.hpp
//! \author jbruel
//! \date 26/09/2017
//!

#ifndef SPIDER_SPIDEREXCEPTION_HPP
#define SPIDER_SPIDEREXCEPTION_HPP

#include <string>
#include <exception>

//!
//! \namespace Spider
//!
namespace Spider
{
	//!
	//! \class SpiderException
	//! \brief Exception interface
	//!
	class   SpiderException : public std::exception
	{
    private:
		std::string     mMsg; //!< Exception message

	public:
		//!
		//! \brief Constructor of the Spider class Exception by default.
		//! \param msg Message related to the exception sent
		//!
		SpiderException(const std::string &msg) : mMsg(msg) {}
		//!
		//! \brief Destructor of class SpiderException
		//!
		virtual ~SpiderException() throw() {}
        //!
        //! \brief Lets you know the identity of the exception
        //! \return Message de l'exception
        //!
        virtual const char  *what() const throw() {return (mMsg.c_str());}
	};
}

#endif //SPIDER_SPIDEREXCEPTION_HPP
