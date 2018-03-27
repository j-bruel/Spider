//
// Created by brd6 on 04/10/17.
//


#ifndef _PingResp_H_
# define _PingResp_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct PingResp :
    	public Request
    {
      PingResp() = default;
      explicit PingResp(std::string const &from, std::string const &to);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;
    };
  }
}

#endif /* !_PingResp_H_ */