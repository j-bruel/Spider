//
// Created by brd6 on 01/10/17.
//


#ifndef _AuthReq_H_
# define _AuthReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct AuthReq :
    	public Request
    {
      std::string pubKey;

      AuthReq() = default;
      explicit AuthReq(std::string const &from,
		       std::string const &to,
		       std::string const &pubKey = "");

      void fromJson(std::string const &json) override;

      std::string toJson() override;

      int getId() const override;
    };
  }
}

#endif /* !_AuthReq_H_ */