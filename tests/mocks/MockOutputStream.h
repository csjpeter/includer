/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IOutputStream.h"
#include <string>

class MockOutputStream : public IOutputStream
{
	public:

	void
	writeLine(const std::string &line) override
	{
		output += line + '\n';
	}

	void
	write(const std::string &content) override
	{
		output += content;
	}

	std::string
	getOutput() const
	{
		return output;
	}

	private:

	std::string output;
};
