/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include <stack>
#include <string>

#include "IFileInputStreamFactory.h"
#include "IInputStream.h"
#include "IOutputStream.h"

#include <string>

class Processor
{
	public:

	explicit Processor(const IInputStream	   &inputStream,
			   IOutputStream	   &outputStream,
			   IFileInputStreamFactory &fileInputStreamFactory,
			   const std::string	   &templateDir);

	void process();

	private:

	enum class CommandResult
	{
		Processed,
		Split,
		NotFound
	};

	void	      processStream(const IInputStream &stream);
	CommandResult processCommand(const std::string &line);
	void	      processInclude(const std::string &filename);
	void	      processTemplateHead(const std::string &filename);
	void	      processTail();

	private:

	const IFileInputStreamFactory &fileInputStreamFactory;
	const IInputStream	      &inputStream;
	IOutputStream		      &outputStream;
	const std::string	       templateDir;
	std::stack<std::string>	       templateTails;
};
