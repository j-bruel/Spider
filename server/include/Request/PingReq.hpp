//
// Created by brd6 on 04/10/17.
//


#ifndef _PingReq_H_
# define _PingReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct PingReq :
    	public Request
    {
      PingReq() = default;
      explicit PingReq(std::string const &from, std::string const &to);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;
    };
  }
}

#endif /* !_PingReq_H_ */