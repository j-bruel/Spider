//
// Created by brd6 on 30/09/17.
//

#include <iostream>
#include <unordered_map>
#include "ProgramOption/ProgramOption.hpp"

namespace ts
{

  ProgramOption::ProgramOption(int ac, char const **av) :
  	mAc(ac),
	mAv(av),
	mOptionsDescription("Options")
  {
    mAppName = boost::filesystem::basename(mAv[0]);
  }

  void ProgramOption::addOption(Option const &option)
  {
    auto completeName = getCompleteOptionName(option.name, option.shortName);

    mOptionsDescription.add_options()
	    (completeName.c_str(),
	     option.description.c_str());

    mOptions.push_back(option);
  }

  std::string ProgramOption::getCompleteOptionName(std::string const &name, std::string const &shortName)
  {
    std::string completeName(name);

    if (!shortName.empty())
      completeName += "," + shortName;

    return completeName;
  }

  void ProgramOption::run()
  {
    try
      {

	boost::program_options::store(boost::program_options::command_line_parser(mAc, mAv)
					      .options(mOptionsDescription)
					      .positional({})
					      .run(),
				      mVariablesMap);
	mVariablesMap.notify();
      }
    catch (boost::program_options::required_option &e)
      {
	throw ProgramOptionException("All required options are not satisfied.");
      }
    catch (boost::program_options::error &e)
      {
	throw ProgramOptionException(std::string(e.what()));
      }
  }

  void ProgramOption::printOptionDescription(std::ostream& out) const
  {
    out << mOptionsDescription << std::endl;
  }

  void ProgramOption::printProgramArguments(std::ostream& out) const
  {
    std::stringstream usage;

    usage << "Usage: " << mAppName;
    auto tmp = assignOptionalOptionWithNotValue();
    if (!tmp.empty())
      usage << " " << tmp;
    tmp = assignOptionWithValue();
    if (!tmp.empty())
      usage << " " << tmp;

    out << usage.str() << std::endl;
  }

  std::string ProgramOption::assignOptionalOptionWithNotValue() const
  {
    std::string tmp;
    std::string names;
    std::unordered_map<std::string, bool> added;

    for (auto &it : mOptions)
      {
	if (!it.shortName.empty() && !it.hasValue())
	  names += it.shortName;
	added[it.shortName] = true;
      }
    if (!names.empty())
      {
	tmp += "[-";
	tmp += names;
	tmp += "]";
      }
    for (auto &it : mOptions)
      {
	if (!it.name.empty() && !it.hasValue() &&
		added.count(it.shortName) <= 0)
	  tmp += " [--" + it.name + "]";
      }
    return tmp;
  }

  std::string ProgramOption::assignOptionWithValue() const
  {
    std::string tmp;

    for (auto &it : mOptions)
      {
	if (!it.hasValue())
	  continue;

	auto name = it.shortName.empty() ? it.name : it.shortName;

	tmp += (!it.isRequired() ? "[" : "");
	tmp += (it.shortName.empty() ? "--" : "-");
	tmp += name;
	tmp += (it.hasValue() ? " arg" : "");
	tmp += (!it.isRequired() ? "]" : "");
	tmp += " ";
      }
    return tmp;
  }

  bool ProgramOption::has(std::string const &name, std::string const &shortName) const
  {
    return mVariablesMap.count(name) > 0 || mVariablesMap.count(shortName) > 0;
  }

  void ProgramOption::printUsage(std::ostream &out) const
  {
    printProgramArguments(out);
    printOptionDescription(out);
  }
}
