//
// Created by brd6 on 04/10/17.
//


#ifndef _ErrorReq_H_
# define _ErrorReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {
    enum ErrorType
    {
      PACKAGE_BROKEN,
      READ_ERROR
    };

    struct ErrorReq :
    	public Request
    {
      ErrorType errorType;
      std::string message;

      ErrorReq() = default;
      explicit ErrorReq(std::string const &from,
			std::string const &to,
			ErrorType errorType,
			std::string const &message);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;
    };
  }
}

#endif /* !_ErrorReq_H_ */