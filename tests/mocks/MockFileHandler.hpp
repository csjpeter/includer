/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include <stdexcept>
#include "IFileHandler.hpp"
#include <unordered_map>

class MockFileHandler : public IFileHandler {
public:
    void addMockFile(const std::string& path, const std::string& content) {
        mockFiles[path] = content;
    }

    std::string readFile(const std::string& path) override {
        if (mockFiles.find(path) != mockFiles.end()) {
            return mockFiles[path];
        }
        throw std::runtime_error("Mock file not found: " + path);
    }

private:
    std::unordered_map<std::string, std::string> mockFiles;
};
