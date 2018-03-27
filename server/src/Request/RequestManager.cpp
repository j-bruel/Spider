//
// Created by brd6 on 01/10/17.
//

#include "Request/AuthReq.hpp"
#include "Request/RequestManager.hpp"

namespace ts
{
  namespace common
  {

    std::string ts::common::RequestManager::decrypt(char const *data,
						    bool useJson)
    {
      return data;
    }

    std::string RequestManager::encrypt(char const *data)
    {
      return data;
    }

    long RequestManager::getCurrentTimeStamp()
    {
      auto tp = std::chrono::system_clock::now();
      auto dtn = tp.time_since_epoch();

      return std::chrono::duration_cast<std::chrono::milliseconds>(dtn).count();
    }

  }
}