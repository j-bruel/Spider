//
// Created by brd6 on 04/10/17.
//

#include "Request/DisconnectReq.hpp"

namespace ts
{
  namespace common
  {

    int DisconnectReq::getId() const
    {
      return RequestId::DISCONNECT_REQ;
    }

    void DisconnectReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);
    }

    std::string DisconnectReq::toJson()
    {
      Request::toJson();

      return mJsonParser.write();
    }

    DisconnectReq::DisconnectReq(std::string const &from, std::string const &to)
    {
      Request::from = from;
      Request::to = to;
    }
  }
}

