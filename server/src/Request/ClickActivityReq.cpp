//
// Created by brd6 on 03/10/17.
//

#include "Request/ClickActivityReq.hpp"

namespace ts
{
  namespace common
  {

    ClickActivityReq::ClickActivityReq(std::string const &from,
				       std::string const &to,
				       ClickType clickType,
				       int clickX,
				       int clickY):
	    clickType(clickType),
	    clickX(clickX),
	    clickY(clickY)
    {
      Request::from = from;
      Request::to = to;
    }

    int ClickActivityReq::getId() const
    {
      return RequestId::CLICK_ACTIVITY_REQ;
    }

    void ClickActivityReq::fromJson(std::string const &json)
    {
      Request::fromJson(json);

      int clickTypeVal = clickType;

      mJsonParser.get("CLICK_TYPE", clickTypeVal);
      mJsonParser.get("CLICK_X", clickX);
      mJsonParser.get("CLICK_Y", clickY);
      mJsonParser.get("PROCESS_INFO", processInfo);

      clickType = static_cast<ClickType>(clickTypeVal);
    }

    std::string ClickActivityReq::toJson()
    {
      Request::toJson();

      mJsonParser.put("CLICK_TYPE", clickType);
      mJsonParser.put("CLICK_X", clickX);
      mJsonParser.put("CLICK_Y", clickY);
      mJsonParser.put("PROCESS_INFO", processInfo);

      return mJsonParser.write();
    }
  }
}

