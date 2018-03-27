//
// Created by brd6 on 04/10/17.
//

#include "Request/PingReq.hpp"

namespace ts
{
  namespace common
  {

    int PingReq::getId() const
    {
      return RequestId::PING_REQ;
    }

    void PingReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);
    }

    std::string PingReq::toJson()
    {
      Request::toJson();

      return mJsonParser.write();
    }

    PingReq::PingReq(std::string const &from, std::string const &to)
    {
      Request::from = from;
      Request::to = to;
    }
  }
}

