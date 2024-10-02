/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "Processor.h"
#include "IFileInputStreamFactory.h"
#include "StringInputStream.h"

#include <filesystem>
#include <iostream>
#include <regex>
#include <stack>

/*
This class shall process input on the fly and write to output.

While doing so, it should parse the input looking for the following
possible commands:
  @include filename@
  @template_head filename@
  @tail@

The filename can be with path and shall be interpreted as relative to the
templateDir.

If include command is found, then the referenced file shall be opened and
processed the same way aas the current input. Thus we gonna need a
recursion here.

If template_head if found, look for the referenced filename and expect it
to be split into two parts, separated by command @split@. Out put the
content till this separator command, and remember the ramaining part as
it have to be sent to ouput once we find the tail command on the input.
If there happened to be no tail command on the input, write the tail part
when the input reached EOF.
There can be multiple tempalte commands and those can be nested.

Any temaplte and include command by be nested event with eachother.

Please describe the grammer with appropriate notations.

Please expect new command to be introduced later.


```ebnf
document = { text | command }
command = include | template_head | tail | split
include = "@include" filename "@"
template_head = "@template_head" filename "@"
tail = "@tail@"
split = "@split@"
filename = { any_character_except_@ }+
text = { any_character_except_@ }+
any_character_except_@ = ? any Unicode character except '@' ?
```

Note: This grammar allows for nested commands as per the requirements.
*/

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

	std::string tailContent = templateTails.top();
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
