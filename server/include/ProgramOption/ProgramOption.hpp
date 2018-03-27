//
// Created by brd6 on 30/09/17.
//

#ifndef _ProgramOption_H_
# define _ProgramOption_H_

#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>
#include <boost/any.hpp>
#include "ProgramOption/ProgramOptionException.hpp"
#include "ProgramOption/Option.hpp"

namespace ts
{
  class ProgramOption
  {
   private:
    std::string mAppName;
    boost::program_options::options_description mOptionsDescription;
    boost::program_options::variables_map mVariablesMap;
    std::vector<Option> mOptions;

    int mAc;
    char const **mAv;

   public:
    ProgramOption(int ac, char const **av);
    ~ProgramOption() = default;

    template <typename TValue>
    void addOption(Option &option)
    {
      auto completeName = getCompleteOptionName(option.name, option.shortName);

      if (option.isRequired())
	mOptionsDescription.add_options()
		(completeName.c_str(),
		 boost::program_options::value<TValue>()->required(),
		 option.description.c_str());
      else
	mOptionsDescription.add_options()
		(completeName.c_str(),
		 boost::program_options::value<TValue>(),
		 option.description.c_str());

      mOptions.push_back(option);
    }

    template <typename TValue>
    void addOption(Option &option, TValue const &defaultValue)
    {
      auto completeName = getCompleteOptionName(option.name, option.shortName);

      if (option.isRequired())
	mOptionsDescription.add_options()
		(completeName.c_str(),
		 boost::program_options::value<TValue>()
			 ->required()
			 ->default_value(defaultValue),
		 option.description.c_str());
      else
	mOptionsDescription.add_options()
		(completeName.c_str(),
		 boost::program_options::value<TValue>()
			 ->default_value(defaultValue),
		 option.description.c_str());

      mOptions.push_back(option);
    }

    void addOption(Option const &option);

    void run();

    void printOptionDescription(std::ostream& out = std::cout) const;
    void printProgramArguments(std::ostream& out = std::cout) const;
    void printUsage(std::ostream& out = std::cout) const;

    bool has(std::string const &name, std::string const &shortName = "") const;

    template<typename TValue>
    TValue get(std::string const &name, std::string const &shortName = "")
    {
      if (has(name))
	return mVariablesMap[name].as<TValue>();
      return mVariablesMap[shortName].as<TValue>();
    }

   private:
    /**
     * Helper for get the name with his short part if exist
     * @return
     */
    std::string getCompleteOptionName(std::string const &name,
				      std::string const &shortName = "");

    std::string assignOptionalOptionWithNotValue() const;
    std::string assignOptionWithValue() const;

  };
}

#endif /* !_ProgramOption_H_ */