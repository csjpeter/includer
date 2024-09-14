/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once
#include "IFileHandler.hpp"

#include <string>

class Processor
{
	public:

	explicit Processor(const IFileHandler &fileHandler);

	std::string process(const std::string &input,
			    const std::string &templateDir);

	private:

	const IFileHandler &fileHandler;

	std::string	    processIncludes(const std::string &input,
					    const std::string &templateDir);
	std::string	    processFrames(const std::string &input,
					  const std::string &templateDir);
};
