/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#pragma once
#include <string>

class IFileHandler {
public:
    virtual std::string readFile(const std::string& path) = 0;
    virtual ~IFileHandler() {}
};
