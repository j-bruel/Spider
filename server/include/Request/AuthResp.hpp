//
// Created by brd6 on 01/10/17.
//


#ifndef _AuthResp_H_
# define _AuthResp_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct AuthResp :
    	public Request
    {
      std::string pubKey;
      bool isAuth;

      explicit AuthResp(std::string const &from,
			std::string const &to,
			std::string const &pubKey,
			bool isAuth);

      int getId() const override;

      std::string toJson() override;
    };
  }
}

#endif /* !_AuthResp_H_ */