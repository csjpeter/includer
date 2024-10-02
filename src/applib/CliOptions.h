/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once
#include <string>

class CliOptions
{
	public:

	CliOptions(int argc, char **argv);
	bool parse();

	std::string
	getTemplateDir() const
	{
		return templateDir;
	}
	bool
	shouldShowHelp() const
	{
		return showHelp;
	}

	private:

	int	    argc;
	char	  **argv;
	std::string templateDir;
	bool	    showHelp = false;
};
