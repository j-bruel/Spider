//
// Created by brd6 on 04/10/17.
//

#include "Request/NoticeReceiptReq.hpp"

namespace ts
{
  namespace common
  {

    NoticeReceiptReq::NoticeReceiptReq(std::string const &from,
				       std::string const &to,
				       unsigned int reqTimestamp,
				       int reqId) :
    	reqTimestamp(reqTimestamp),
	reqId(reqId)

    {
      Request::from = from;
      Request::to = to;
    }

    int NoticeReceiptReq::getId() const
    {
      return RequestId::NOTICE_RECEIPT_REQ;
    }

    void NoticeReceiptReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      mJsonParser.get("REQ_TIMESTAMP", reqTimestamp);
      mJsonParser.get("REQ_ID", reqId);
    }

    std::string NoticeReceiptReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("REQ_TIMESTAMP", reqTimestamp);
      mJsonParser.put("REQ_ID", reqId);

      return mJsonParser.write();
    }
  }
}

