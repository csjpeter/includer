/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "CliOptions.h"
#include <cxxopts.hpp>
#include <iostream>

CliOptions::CliOptions(int argc, char **argv) : argc(argc), argv(argv)
{
}

bool
CliOptions::parse()
{
	cxxopts::Options options(
			"template_processor",
			"A program to process include and frame commands");

	options.add_options()("t,template", "Template directory",
			      cxxopts::value<std::string>())("h,help",
							     "Print usage");

	auto result = options.parse(argc, argv);

	if (result.count("help"))
	{
		showHelp = true;
		std::cout << options.help() << std::endl;
		return false;
	}

	if (!result.count("template"))
	{
		std::cerr << "Template directory is required (-t or --template)"
			  << std::endl;
		return false;
	}

	templateDir = result["template"].as<std::string>();
	return true;
}
