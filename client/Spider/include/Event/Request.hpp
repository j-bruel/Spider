//!
//! \file EventHandler.hpp
//! \author jbruel
//! \date 03/10/2017
//!

#ifndef SPIDER_NETWORK_REQUEST_HPP
#define SPIDER_NETWORK_REQUEST_HPP

#include <string>
#include <memory>
#include <unordered_map>
#include <ctime>
#include "Event/IEvent.hpp"
#include "ssl/RSAKeys.hpp"

//!
//! \namespace Spider
//!
namespace Spider
{
//!
//! \namespace Network
//!
namespace Event
{
	//!
	//! \class Request
	//! \brief Request informations container
	//!
	class Request
	{
	private:
		//!
		//! \enum Variables
		//! \brief All the variables availables on the spider project
		//!
		enum Variables
		{
			PUB_KEY,
			IS_AUTH,
			CLICK_TYPE,
			CLICK_X,
			CLICK_Y,
			PROCESS_iNFO,
			KEYS,
			REQ_TIMESTAMP,
			REQ_ID,
			ERROR_TYPE,
			MESSAGE
		};

		//!
		//! \enum Names
		//! \brief All the requests name from the spider project
		//!
		enum Names
		{
			AUTH_REQ,
			AUTH_RESP,
			CLICK_ACTIVITY_REQ,
			MOVE_ACTIVITY_REQ,
			KEY_INFO_REQ,
			PING_REQ,
			PING_RESP,
			NOTICE_RECEIPT_REQ,
			ERROR_REQ,
			DISCONNECT_REQ
		};

		//!
		//! \enum ErrorType
		//! \brief Error type from a faild request
		//!
		enum ErrorType
		{
			PACKAGE_BROKEN,
			READ_ERROR
		};
		
		//!
		//! \enum CLICK_TYPE
		//! \brief Describe the type of a click
		//!
		enum CLICK_TYPE
		{
			RIGHT,
			MIDDLE,
			LEFT
		};

	private:
		const std::unordered_map<Variables, std::string>	mVariables{ { PUB_KEY , "PUB_KEY"},
																		{ IS_AUTH , "IS_AUTH"},
																		{ CLICK_TYPE , "CLICK_TYPE"},
																		{ CLICK_X , "CLICK_X"},
																		{ CLICK_Y , "CLICK_Y"},
																		{ PROCESS_iNFO , "PROCESS_iNFO"},
																		{ KEYS , "KEYS"},
																		{ REQ_TIMESTAMP , "REQ_TIMESTAMP"},
																		{ REQ_ID , "REQ_ID"},
																		{ ERROR_TYPE , "ERROR_TYPE"},
																		{ MESSAGE , "MESSAGE"} }; //!< Relation from the Spider Varibles and his string

		const std::unordered_map<Names, int>	mNames{ { AUTH_REQ , 1},
														{ AUTH_RESP , 2},
														{ CLICK_ACTIVITY_REQ , 3},
														{ MOVE_ACTIVITY_REQ , 4},
														{ KEY_INFO_REQ , 5},
														{ PING_REQ , 6},
														{ PING_RESP , 7},
														{ NOTICE_RECEIPT_REQ , 8},
														{ ERROR_REQ , 9},
														{ DISCONNECT_REQ , 10 } }; //!< Relation from the spider request and his define number on the RFC

	private:
		size_t			mSize; //!< Package size

	public:
		size_t			mRequestIdx; //!< Idx from the request
		std::string		mFrom; //!< Sender name
		std::string		mTo; //!< Receiver name
		std::time_t		mTimestamp; //!< Time where the package is create
		std::shared_ptr<Event::IEvent>	mEvent; //!< Event of request

	public:
		//!
		//! \brief Default constructor
		//!
		Request() : mRequestIdx(0), mSize(0), mFrom(""), mTo(""), mTimestamp(std::time(nullptr)), mEvent(nullptr) {}
		//!
		//! \brief Default copy constructor
		//!
		Request(const Request &request);
		//!
		//! \brief Equal operator overload
		//!
		Request	&operator=(const Request &request) = delete;
		//!
		//! \brief Default destructor
		//!
		~Request() = default;

	public:
		//!
		//! \brief Request generator
		//! \param requestId Id of the request to generate
		//! \param rsa RSA keys to crypt the data
		//! \param isCrypt Indicator to know if the request need to be crypted
		//!
		std::string	generate(int requestId, const ssl::RSAKeys &rsa, bool isCrypt) const;

	private:
		//!
		//! \brief Create a header for the request
		//! \param requestId Id of the request to generate
		//! \param requestSize Size of the request to generate
		//!
		std::string	createHeader(const int &requestId, const int &requestSize) const;
	};
}
}

#endif //SPIDER_NETWORK_REQUEST_HPP
