//
// Created by brd6 on 06/10/17.
//


#ifndef _SqliteDataRecorder_H_
# define _SqliteDataRecorder_H_

#include "IDataRecorder.hpp"
#include "Db/DBServerHandler.hpp"


namespace ts
{
  class SqliteDataRecorder :
  	public IDataRecorder
  {
   private:
    Spider::DB::DBServerHandler mDbServerHandler;
    bool mIsInitialized;

   public:
    void initialize(std::string const &name) override;
    void save(common::Request &request) override;
  };
}

#endif /* !_SqliteDataRecorder_H_ */