//
// Created by brd6 on 03/10/17.
//

#ifndef _CommandReq_H_
# define _CommandReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    struct CommandReq :
	    public Request
    {
      std::string msg;

      explicit CommandReq(std::string const &from,
			  std::string const &to,
			  std::string const &msg);

      void fromJson(std::string const &json) override;

      int getId() const override;

      std::string toJson() override;
    };
  }
}

#endif /* !_CommandReq_H_ */