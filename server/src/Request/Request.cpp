//
// Created by brd6 on 01/10/17.
//

#include <Json/JsonParser.hpp>
#include <iostream>
#include "Request/Request.hpp"

namespace ts
{
  namespace common
  {

    void ts::common::Request::fromJson(const std::string &json)
    {
      mJsonParser.parse(json);

      mJsonParser.get("FROM", from);
      mJsonParser.get("TO", to);
      mJsonParser.get("TIMESTAMP", timestamp);
    }

    std::string Request::toJson()
    {
      mJsonParser.put("FROM", from);
      mJsonParser.put("TO", to);
      mJsonParser.put("TIMESTAMP", timestamp);

      return {};
    }
  }
}

