/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"
#include <stdexcept>
#include <string>

class MockInputStream : public IInputStream
{
	public:

	MockInputStream(const std::string &content)
			: content(content), position(0)
	{
	}

	bool
	hasNext() const override
	{
		return position < content.length();
	}

	char
	readChar() const override
	{
		if (hasNext())
		{
			return content[position++];
		}
		throw std::out_of_range("No more characters to read");
	}

	private:

	std::string    content;
	mutable size_t position;
};
