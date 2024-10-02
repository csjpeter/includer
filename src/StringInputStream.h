/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"

#include <string>

class StringInputStream : public IInputStream
{
	public:

	explicit StringInputStream(const std::string &str)
			: data(str), position(0)
	{
	}

	bool
	hasNext() const override
	{
		return position < data.length();
	}

	char
	readChar() const override
	{
		if (hasNext())
		{
			return data[position++];
		}
		return '\0'; // Return null character if we've reached the end
	}

	private:

	std::string    data;
	mutable size_t position;
};
