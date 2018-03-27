//
// Created by brd6 on 03/10/17.
//

#include "Request/KeyInfoReq.hpp"

namespace ts
{
  namespace common
  {

    KeyInfoReq::KeyInfoReq(std::string const &from,
			   std::string const &to,
			   std::string const &keys,
			   std::string const &processInfo) :
    	keys(keys),
	processInfo(processInfo)
    {
      Request::from = from;
      Request::to = to;
    }

    int KeyInfoReq::getId() const
    {
      return RequestId::KEY_INFO_REQ;
    }

    void KeyInfoReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      mJsonParser.get("KEYS", keys);
    }

    std::string KeyInfoReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("KEYS", keys);

      return mJsonParser.write();
    }
  }
}