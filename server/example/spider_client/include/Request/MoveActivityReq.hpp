//
// Created by brd6 on 01/10/17.
//


#ifndef _MoveActivityReq_H_
# define _MoveActivityReq_H_

#include <vector>
#include "Request.hpp"

namespace ts
{
  namespace common
  {
    // TODO : Use map !
    struct MoveActivityReq :
    	public Request
    {
      std::vector<int> clicksX;
      std::vector<int> clicksY;
      std::string processInfo;
    };
  }
}

#endif /* !_MoveActivityReq_H_ */