//
// Created by brd6 on 01/10/17.
//


#ifndef _JsonParser_H_
# define _JsonParser_H_

#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <vector>

namespace ts
{
  namespace common
  {
    class JsonParser
    {
     private:
      boost::property_tree::ptree mRoot;

     public:
      JsonParser() = default;
      ~JsonParser() = default;

      void parse(std::string const &json);

      template <typename TValue>
      void get(std::string const &path, TValue &value) const
      {
	value = mRoot.get<TValue>(path);
      }

      template <typename TValue, typename TKey = TValue>
      void get(std::string const &path,
	       std::vector<std::pair<TKey, TValue>> &values) const
      {
	for (auto &it : mRoot.get_child(path))
	  {
	    auto key = it.first;
	    auto value = it.second.data();

	    values.push_back(std::make_pair(key, value));
	  }
      }

      template <typename TValue>
      void get(std::string const &path, std::vector<TValue> &values)
      {
	for (auto &it : mRoot.get_child(path))
	  {
	    values.push_back(it.second.data());
	  }
      }

      void clear();

      template <typename TValue>
      void put(std::string const &path, TValue const &value)
      {
	mRoot.put(path, value);
      }

      std::string write();

    };
  }
}

#endif /* !_JsonParser_H_ */