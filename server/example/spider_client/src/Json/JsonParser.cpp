//
// Created by brd6 on 01/10/17.
//

#include <sstream>
#include <iostream>
#include "Json/JsonParser.hpp"

namespace ts
{
  namespace common
  {
    void JsonParser::parse(std::string const &json)
    {
      std::istringstream is(json);

      boost::property_tree::json_parser::read_json(is, mRoot);
    }

    std::string JsonParser::write()
    {
      std::stringstream ss;

      boost::property_tree::json_parser::write_json(ss, mRoot);

      return ss.str();
    }

    void JsonParser::clear()
    {
      mRoot.clear();
    }

  }
}