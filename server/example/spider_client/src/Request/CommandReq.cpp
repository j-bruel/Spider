//
// Created by brd6 on 03/10/17.
//

#include <iostream>
#include "Request/CommandReq.hpp"

namespace ts
{
  namespace common
  {

    CommandReq::CommandReq(std::string const &from,
			   std::string const &to,
			   std::string const &msg) :
    	msg(msg)
    {
      Request::from = from;
      Request::to = to;
    }

    void CommandReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      mJsonParser.get("MSG", msg);
    }

    int CommandReq::getId() const
    {
      return RequestId::COMMAND_REQ;
    }

    std::string CommandReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("MSG", msg);

      return mJsonParser.write();
    }
  }
}
