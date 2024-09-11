/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once
#include "IFileHandler.hpp"

#include <memory>
#include <string>

class Processor
{
    public:
	Processor(std::shared_ptr<IFileHandler> fileHandler);
	std::string
	process(const std::string &input, const std::string &templateDir);

    private:
	std::shared_ptr<IFileHandler> fileHandler;

	std::string
	parse(const std::string &input, const std::string &templateDir);
	std::string processIncludes(const std::string &input,
				    const std::string &templateDir);
	std::string
	processFrames(const std::string &input, const std::string &templateDir);
};
