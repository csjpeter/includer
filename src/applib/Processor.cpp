/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "Processor.h"
#include "IFileInputStreamFactory.h"
#include "IOutputStream.h"
#include "IInputStream.h"
#include "StringInputStream.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <stack>

Processor::Processor(const IInputStream	     &inputStream,
		     IOutputStream	     &outputStream,
		     IFileInputStreamFactory &fileInputStreamFactory,
		     const std::string	     &templateDir)
		: inputStream(inputStream), outputStream(outputStream),
		  fileInputStreamFactory(fileInputStreamFactory),
		  templateDir(templateDir)
{
}

void
Processor::process()
{
	processStream(inputStream);
}

void
Processor::processStream(const IInputStream &stream)
{
	std::string buffer;

	while (stream.hasNext())
	{
		char c = 0;
		try
		{
			c = stream.readChar();
		}
		catch (std::runtime_error &e)
		{
			std::cerr << e.what() << std::endl;
			// FIXME this is some kind of bug that this is needed at
			// all
			break;
		}
		buffer += c;

		if (c == '@')
		{
			CommandResult result = processCommand(buffer);
			if (result == CommandResult::Processed)
			{
				buffer.clear();
				continue;
			}
			else if (result == CommandResult::Split)
			{
				return;
			}
		}

		// Arbitrary limit to prevent excessive memory usage
		// Wee need to keep as many bytes as many might be
		// used by an unfinished command in the buffer
		if (buffer.length() > 1500)
		{
			outputStream.write(buffer.substr(
					0, buffer.length() - 1000));
			buffer = buffer.substr(buffer.length() - 1000);
		}
	}

	// Output remaining buffer
	if (!buffer.empty())
	{
		outputStream.write(buffer);
	}

	// Write remaining template tails if any
	while (!templateTails.empty())
	{
		processTail();
	}
}

Processor::CommandResult
Processor::processCommand(const std::string &buffer)
{
	static const std::regex includeRegex("@include (.+?)@");
	static const std::regex templateHeadRegex("@template_head (.+?)@");
	static const std::regex tailRegex("@tail@");
	static const std::regex splitRegex("@split@");

	std::smatch		match;

	if (std::regex_search(buffer, match, includeRegex))
	{
		outputStream.write(buffer.substr(0, match.position()));
		processInclude(match[1]);
		return CommandResult::Processed;
	}
	else if (std::regex_search(buffer, match, templateHeadRegex))
	{
		outputStream.write(buffer.substr(0, match.position()));
		processTemplateHead(match[1]);
		return CommandResult::Processed;
	}
	else if (std::regex_search(buffer, match, tailRegex))
	{
		outputStream.write(buffer.substr(0, match.position()));
		processTail();
		return CommandResult::Processed;
	}
	else if (std::regex_search(buffer, match, splitRegex))
	{
		outputStream.write(buffer.substr(0, match.position()));
		// buffer = buffer.substr(0, buffer.length() - 7); // Remove
		// "@split@"
		return CommandResult::Split;
	}

	return CommandResult::NotFound;
}

void
Processor::processTemplateHead(const std::string &filename)
{
	std::filesystem::path filePath
			= std::filesystem::path(templateDir) / filename;
	const auto templateStream
			= fileInputStreamFactory.create(filePath.string());
	//outputStream.write("<!-- template head "+filePath.string()+" -->");
	std::cerr << "<!-- template head "+filePath.string()+" -->" << std::endl;

	// Process the head part until @split@ is found
	processStream(*templateStream);

	std::string tail;

	// Read the rest of the file into tail
	while (templateStream->hasNext())
	{
		tail += templateStream->readChar();
	}

	// Store the tail for later processing
	// Empty tail is important too because of nesting support
	templateTails.push(tail);
}

void
Processor::processTail()
{
	if (templateTails.empty())
	{
		return; // Silently ignore @tail@ command if there's no matching
			// @template_head@
	}

	std::string tailContent = std::move(templateTails.top());
	templateTails.pop();
	//outputStream.write("<!-- template tail -->");
	std::cerr << "<!-- template tail -->" << std::endl;
	// Process the tail part, allowing for nested commands
	StringInputStream tailStream(tailContent);
	processStream(tailStream);
}

void
Processor::processInclude(const std::string &filename)
{
	std::filesystem::path filePath
			= std::filesystem::path(templateDir) / filename;
	//outputStream.write("<!-- including "+filePath.string()+" -->");
	std::cerr << "<!-- including "+filePath.string()+" -->" << std::endl;
	const auto includeStream
			= fileInputStreamFactory.create(filePath.string());
	processStream(*includeStream);
}
