//
// Created by brd6 on 01/10/17.
//


#ifndef _Request_H_
# define _Request_H_

#include <string>
#include "Json/JsonParser.hpp"

namespace ts
{
  namespace common
  {
    enum RequestId
    {
      AUTH_REQ = 1,
      AUTH_RESP,
      CLICK_ACTIVITY_REQ,
      KEY_INFO_REQ,
      PING_REQ,
      PING_RESP,
      NOTICE_RECEIPT_REQ,
      ERROR_REQ,
      DISCONNECT_REQ,
      COMMAND_REQ
    };

    struct Request
    {
      std::string from;
      std::string to;
      std::string timestamp;

      virtual int getId() const = 0;

      virtual void fromJson(std::string const &json);
      virtual std::string toJson();

     protected:
      common::JsonParser mJsonParser;
    };
  }
}

#endif /* !_Request_H_ */