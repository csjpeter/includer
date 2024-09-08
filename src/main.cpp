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
