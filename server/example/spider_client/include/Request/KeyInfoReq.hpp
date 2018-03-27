//
// Created by brd6 on 03/10/17.
//


#ifndef _KeyInfoReq_H_
# define _KeyInfoReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct KeyInfoReq :
    	public Request
    {
      std::string keys;
      std::string processInfo;

      KeyInfoReq() = default;

      explicit KeyInfoReq(std::string const &from,
			  std::string const &to,
			  std::string const &keys,
			  std::string const &processInfo);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;

    };
  }
}

#endif /* !_KeyInfoReq_H_ */