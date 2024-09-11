/**
 * @author Peter Csaszar (Császár Péter) (Copyright) 2024
 */

#if 0
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <cxxopts.hpp>
#include <stdexcept>

// Function to replace @include@ directives with file contents
void replaceIncludes(std::istream &input, std::ostream &output,
                     const std::string &templateDir) {
    std::regex includePattern(R"(@include@\s+(\S+))");
    std::string line;

    while (std::getline(input, line)) {
        std::smatch match;
        if (!std::regex_search(line, match, includePattern)) {
            output << line << '\n';
            continue;
        }

        std::string includeFile = templateDir + "/" + match[1].str();
        std::ifstream file(includeFile);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open file: " + includeFile);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        line.replace(match.position(), match.length(), buffer.str());
        output << line << '\n';
    }
}

// Function to parse CLI arguments
void cliArgParse(int argc, char *argv[], std::string &templateDir) {
    cxxopts::Options options("include_replacer",
        "Replace @include@ with the content of files from a template directory.");
    options.add_options()
        ("t,template", "Template directory", cxxopts::value<std::string>())
        ("h,help", "Print help message");

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        throw std::runtime_error("Help requested");
    }

    if (result.count("template")) {
        templateDir = result["template"].as<std::string>();
        return;
    }

    throw std::runtime_error("Template directory must be specified with -t or --template");
}

int main(int argc, char *argv[]) {
    std::string templateDir;

    try {
        cliArgParse(argc, argv, templateDir);
        replaceIncludes(std::cin, std::cout, templateDir);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
#endif

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
