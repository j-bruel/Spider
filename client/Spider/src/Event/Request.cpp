//!
//! \file EventHandler.hpp
//! \author jbruel
//! \date 03/10/2017
//!

#include <string>
#include <cstdlib>
#include <sstream>
#include "Event/Request.hpp"
#include "ssl/RSAKeys.hpp"

namespace Spider
{
namespace Event
{
	Request::Request(const Request &request)
	{
		mSize = request.mSize;
		mRequestIdx = request.mRequestIdx;
		mFrom = request.mFrom;
		mTo = request.mTo;
		mTimestamp = request.mTimestamp;
		mEvent = request.mEvent;
	}

	std::string	Request::generate(int requestId, const ssl::RSAKeys &rsa, bool isCrypted) const
	{
		std::stringstream	ssJson;
		
		ssJson << "{" << "\"FROM\":\"" << mFrom << "\",\"TO\":\"" + mTo << "\",\"TIMESTAMP\":\"" << mTimestamp << "\"," << mEvent->getEventInfo() << "}";

		std::string			json(ssJson.str());

		if (!isCrypted)
			return (json);
        return (json);
	}

/*	std::string	Request::createHeader(const int &requestId, const int &requestSize) const
	{
		std::stringstream	header;
		int		nbRId = 0;
		int		reqId = requestId;
		int		reqSize = requestSize;
		int		nbRSize = 0;

		while (reqId > 0)
		{
			reqId /= 10;
			nbRId += 1;
		}
		while (reqSize > 0)
		{
			reqSize /= 10;
			nbRSize += 1;
		}
		for (int i = 0; i < (4 - nbRId); ++i)
			header << '0';
		header << requestId;
		for (int i = 0; i < (4 - nbRSize); ++i)
			header << '0';
		header << requestSize;
		return (header.str());
	}*/
}
}