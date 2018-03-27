//
// Created by brd6 on 06/10/17.
//

#include "DataRecorder/SqliteDataRecorder.hpp"

namespace ts
{
  void SqliteDataRecorder::save(common::Request &request)
  {
    mDbServerHandler.push(request);
  }

  void SqliteDataRecorder::initialize(std::string const &name)
  {
    mDbServerHandler.connect(name);
    mIsInitialized = true;
  }
}