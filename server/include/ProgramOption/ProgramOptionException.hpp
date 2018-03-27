//
// Created by brd6 on 02/10/17.
//


#ifndef _ProgramOptionException_H_
# define _ProgramOptionException_H_

namespace ts
{
  class ProgramOptionException :
	  public std::exception
  {
   private:
    std::string mMsg;

   public:
    explicit ProgramOptionException(std::string const &msg) : mMsg(msg) {};

    virtual const char *what() const throw()
    {
      return mMsg.c_str();
    }
  };
}

#endif /* !_ProgramOptionException_H_ */