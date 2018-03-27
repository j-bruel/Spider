//
// Created by brd6 on 04/10/17.
//


#ifndef _DisconnectReq_H_
# define _DisconnectReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct DisconnectReq :
    	public Request
    {
      DisconnectReq() = default;

      explicit DisconnectReq(std::string const &from, std::string const &to);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;
    };
  }
}

#endif /* !_DisconnectReq_H_ */