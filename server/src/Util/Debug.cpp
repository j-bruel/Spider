//
// Created by brd6 on 05/10/17.
//

#include <iostream>

#include "Util/Debug.hpp"

namespace ts
{
  namespace common
  {

    std::ostream *Debug::mOs;
    Debug::DebugType mDefaultType = Debug::DebugType::Info;

    Debug::Debug(Debug::DebugType type) :
    	mType(type)
    {
      if (mOs == nullptr)
	init(mType);
    }

    void Debug::init(Debug::DebugType type, std::ostream &os)
    {
      mOs = &os;
    }

    std::string Debug::getCurrentDateTime()
    {
      time_t now = time(nullptr);
      tm  tstruct{};
      char buf[80];

      tstruct = *localtime(&now);
      strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

      return buf;
    }

    Debug &Debug::setType(Debug::DebugType type)
    {
      mType = type;
      return *this;
    }
  }
}
