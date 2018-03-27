//
// Created by brd6 on 06/10/17.
//


#ifndef _IDataRecorder_H_
# define _IDataRecorder_H_

#include "Request/Request.hpp"

namespace ts
{
  class IDataRecorder
  {
   public:
    virtual void initialize(std::string const &name) = 0;
    virtual void save(common::Request &request) = 0;

  };
}

#endif /* !_IDataRecorder_H_ */