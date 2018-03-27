//
// Created by brd6 on 04/10/17.
//


#ifndef _NoticeReceiptReq_H_
# define _NoticeReceiptReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct NoticeReceiptReq :
    	public Request
    {
      unsigned int reqTimestamp;
      int reqId;

      NoticeReceiptReq() = default;
      explicit NoticeReceiptReq(std::string const &from,
				std::string const &to,
				unsigned int reqTimestamp,
				int reqId);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;

    };
  }
}

#endif /* !_NoticeReceiptReq_H_ */