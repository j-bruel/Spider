//
// Created by brd6 on 01/10/17.
//

#include "Request/AuthResp.hpp"

namespace ts
{
  namespace common
  {

    int AuthResp::getId() const
    {
      return RequestId::AUTH_RESP;
    }

    std::string AuthResp::toJson()
    {
      Request::toJson();

      mJsonParser.put("PUB_KEY", pubKey);
      mJsonParser.put<bool>("IS_AUTH", isAuth);

      auto json = mJsonParser.write();

      return json;
    }

    AuthResp::AuthResp(std::string const &from,
		       std::string const &to,
		       std::string const &pubKey,
		       bool isAuth) :
	    pubKey(pubKey),
	    isAuth(isAuth)
    {
      Request::from = from;
      Request::to = to;
    }
  }
}

