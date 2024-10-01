/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"
#include <fstream>
#include <string>

class FileInputStream : public IInputStream
{
	public:

	explicit FileInputStream(const std::string &filename) : file(filename)
	{
	}

	bool
	hasNext() const override
	{
		return file.peek() != EOF;
	}

	char
	readChar() const override
	{
		char c;
		file.get(c);
		return c;
	}

	private:

	mutable std::ifstream file;
};
