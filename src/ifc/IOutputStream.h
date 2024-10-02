/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once

#include <string>

class IOutputStream
{
	public:

	virtual ~IOutputStream()			= default;
	virtual void writeLine(const std::string &line) = 0;
	virtual void write(const std::string &content)	= 0;
};
