//
// Created by brd6 on 01/10/17.
//


#ifndef _ClickActivityReq_H_
# define _ClickActivityReq_H_

#include "Request.hpp"

namespace ts
{
  namespace common
  {

    enum ClickType
    {
      RIGHT,
      MIDDLE,
      LEFT
    };

    struct ClickActivityReq :
    	public Request
    {
      ClickType clickType;
      int clickX;
      int clickY;
      std::string processInfo;

      ClickActivityReq() = default;

      explicit ClickActivityReq(std::string const &from,
				std::string const &to,
				ClickType type,
				int clickX,
				int clickY);

      int getId() const override;

      void fromJson(std::string const &json) override;

      std::string toJson() override;
    };
  }
}

#endif /* !_ClickActivityReq_H_ */