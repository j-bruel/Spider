//
// Created by brd6 on 02/10/17.
//


#ifndef _Option_H_
# define _Option_H_

namespace ts
{
  struct Option
  {
    std::string name;
    std::string shortName;
    std::string description;

    explicit Option(std::string const &description = "",
		    std::string const &name = "",
		    std::string shortName = "") :
	    name(name),
	    shortName(shortName),
	    description(description),
	    required(false),
	    withValue(false)
    {

    }

    bool isRequired() const
    {
      return required;
    }

    bool hasValue() const
    {
      return withValue;
    }

    void setIsRequired(bool state)
    {
      required = state;
    }

    void setHasValue(bool state)
    {
      withValue = true;
    }

   protected:
    bool required;
    bool withValue;
  };
}

#endif /* !_Option_H_ */