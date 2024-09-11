/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "Processor.hpp"

#include <regex>
#include <stdexcept>

Processor::Processor(std::shared_ptr<IFileHandler> fileHandler)
		: fileHandler(fileHandler)
{
}

std::string
Processor::process(const std::string &input, const std::string &templateDir)
{
	return parse(input, templateDir);
}

std::string
Processor::parse(const std::string &input, const std::string &templateDir)
{
	std::string output = input;
	output		   = processIncludes(output, templateDir);
	output		   = processFrames(output, templateDir);
	return output;
}

std::string
Processor::processIncludes(const std::string &input,
			   const std::string &templateDir)
{
	std::regex  includeRegex(R"(@include\s+([^\s]+)@)");
	std::string output = input;
	std::smatch match;
	while (std::regex_search(output, match, includeRegex))
	{
		std::string includeFile = templateDir + "/" + match[1].str();
		std::string fileContent = fileHandler->readFile(includeFile);
		output			= match.prefix().str() + fileContent
		       + match.suffix().str();
	}
	return output;
}

std::string
Processor::processFrames(const std::string &input,
			 const std::string &templateDir)
{
	std::regex  frameRegex(R"(@frame\s+([^\s]+)@)");
	std::string output = input;
	std::smatch match;
	while (std::regex_search(output, match, frameRegex))
	{
		std::string frameFile	 = templateDir + "/" + match[1].str();
		std::string frameContent = fileHandler->readFile(frameFile);

		size_t contentPos = frameContent.find("@content@");
		if (contentPos == std::string::npos)
		{
			throw std::runtime_error(
					"No @content@ marker in frame file: "
					+ frameFile);
		}

		std::string head = frameContent.substr(0, contentPos);
		std::string tail = frameContent.substr(
				contentPos + 9); // length of "@content@"
		output = match.prefix().str() + head + input + tail
		       + match.suffix().str();
	}
	return output;
}
