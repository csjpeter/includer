/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once
#include "IFileHandler.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

class FileHandler : public IFileHandler {
public:
	FileHandler() = default;
	~FileHandler() = default;
    std::string readFile(const std::string & filepath) override;
};
