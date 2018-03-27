//
// Created by brd6 on 04/10/17.
//

#include "Request/ErrorReq.hpp"

namespace ts
{
  namespace common
  {

    ts::common::ErrorReq::ErrorReq(const std::string &from,
				   const std::string &to,
				   ErrorType errorType,
				   const std::string &message) :
    	errorType(errorType),
	message(message)
    {
      Request::from = from;
      Request::to = to;
    }

    int ErrorReq::getId() const
    {
      return RequestId::ERROR_REQ;
    }

    void ErrorReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      int type = 0;

      mJsonParser.get("ERROR_TYPE", type);
      mJsonParser.get("MESSAGE", message);

      errorType = static_cast<ErrorType>(type);
    }

    std::string ErrorReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("ERROR_TYPE", errorType);
      mJsonParser.put("MESSAGE", message);

      return mJsonParser.write();
    }
  }
}

