//
// Created by brd6 on 01/10/17.
//

#include <iostream>
#include "Request/AuthReq.hpp"

namespace ts
{
  namespace common
  {
    void AuthReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      mJsonParser.get("PUB_KEY", pubKey);
    }

    int AuthReq::getId() const
    {
      return RequestId::AUTH_REQ;
    }

    AuthReq::AuthReq(std::string const &from,
		     std::string const &to,
		     std::string const &pubKey) :
    	pubKey(pubKey)
    {
      Request::from = from;
      Request::to = to;
    }

    std::string AuthReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("PUB_KEY", pubKey);

      return mJsonParser.write();
    }
  }
}

