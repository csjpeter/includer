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
	std::string output = input;
	output = processFrames(output, templateDir);
	output = processIncludes(output, templateDir);
	return output;
}

std::string
Processor::processIncludes(const std::string &input,
			   const std::string &templateDir)
{
	std::regex  includeRegex(R"(@include\s+([^\s]+)@)");
	std::string output(input);
	std::smatch match;
	while (std::regex_search(output, match, includeRegex))
	{
		std::string includeFile = templateDir + "/" + match[1].str();
		std::string fileContent = fileHandler->readFile(includeFile);

		Processor processor(fileHandler);

		std::string tmp;
		tmp = match.prefix().str();
		tmp += processor.process(fileContent, templateDir);
		tmp += match.suffix().str();
		output = tmp;
	}
	return output;
}

std::string
Processor::processFrames(const std::string &input,
			 const std::string &templateDir)
{
	std::regex  frameRegex(R"(@frame\s+([^\s]+)@)");
	std::string output(input);
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

		Processor processor(fileHandler);

		std::string tmp = processor.process(head, templateDir);
		tmp += match.prefix().str();
		tmp += match.suffix().str();
		tmp += processor.process(tail, templateDir);
		output = tmp;
	}
	return output;
}
