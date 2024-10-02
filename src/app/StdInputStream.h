/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IInputStream.h"
#include <iostream>

class StdInputStream : public IInputStream
{
	public:

	StdInputStream()
	{
		std::cin.exceptions(std::ios::failbit | std::ios::badbit);
	}

	bool
	hasNext() const override
	{
		return !std::cin.eof();
	}

	char
	readChar() const override
	{
		char c;
		try
		{
			std::cin.get(c);
		}
		catch (const std::ios_base::failure &e)
		{
			if (std::cin.eof())
			{
				throw std::runtime_error("End of standard "
							 "input reached");
			}
			throw std::runtime_error(
					"Error reading standard input: "
					+ std::string(e.what()));
		}
		return c;
	}
};
