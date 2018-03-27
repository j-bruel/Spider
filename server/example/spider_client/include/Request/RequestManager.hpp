//
// Created by brd6 on 01/10/17.
//


#ifndef _RequestManager_H_
# define _RequestManager_H_

#include <set>
#include <stdexcept>
#include <chrono>
#include <iostream>

namespace ts
{
  namespace common
  {
    class RequestManager
    {
     public:
      RequestManager() = default;
      std::string decrypt(char const *data,
			  bool useJson = false);

      template <typename TRequest>
      TRequest decrypt(char const *data)
      {
	auto dataDecrypted = decrypt(data, true);

	if (dataDecrypted.empty())
	  throw std::logic_error("decrypt data error");

	TRequest request;

	request.fromJson(data);

	return request;
      }

      std::string encrypt(char const *data);


      template <typename TRequest, typename... TArgs>
      std::pair<TRequest, std::string> prepare(TArgs &&... args)
      {
	TRequest request(std::forward<TArgs>(args)...);

	request.timestamp = std::to_string(getCurrentTimeStamp());

	auto jsonRequest = request.toJson();
	auto data = jsonRequest.c_str();
	auto encryptedJsonRequest = encrypt(data);

	return {request, encryptedJsonRequest};
      }

     private:
      long getCurrentTimeStamp();

    };
  }
}

#endif /* !_RequestManager_H_ */