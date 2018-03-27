//
// Created by brd6 on 04/10/17.
//

#include "Request/PingResp.hpp"

namespace ts
{
  namespace common
  {

    int PingResp::getId() const
    {
      return RequestId::PING_RESP;
    }

    void PingResp::fromJson(std::string const &json)
    {
      Request::fromJson(json);
    }

    std::string PingResp::toJson()
    {
      Request::toJson();

      return mJsonParser.write();
    }

    PingResp::PingResp(const std::string &from, const std::string &to)
    {
      Request::from = from;
      Request::to = to;
    }
  }
}

