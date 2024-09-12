/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#include <iostream>
#include <sstream>
#include "Processor.hpp"
#include "FileHandler.hpp"
#include "CliOptions.hpp"

int main(int argc, char** argv) {
    CliOptions options(argc, argv);
    if (!options.parse()) {
        return 1;
    }

    std::shared_ptr<IFileHandler> fileHandler = std::make_shared<FileHandler>(); // Real file handler
    Processor processor(fileHandler);

    std::stringstream inputBuffer;
    inputBuffer << std::cin.rdbuf(); // Read from stdin
    std::string input = inputBuffer.str();

    try {
        std::string output = processor.process(input, options.getTemplateDir());
        std::cout << output;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
