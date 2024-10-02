/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include "IOutputStream.h"
#include <iostream>
#include <ostream>

class StdOutputStream : public IOutputStream
{
	public:

	void
	writeLine(const std::string &line) override
	{
		std::cout << line << std::endl;
	}

	void
	write(const std::string &content) override
	{
		std::cout << content;
	}
};
