/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include "FileHandler.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string
FileHandler::readFile(const std::string &path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file: " + path);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
