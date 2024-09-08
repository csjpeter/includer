cmake_minimum_required(VERSION 3.10)
project(includer VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include Conan setup
#include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(src)

include(CTest)
#add_subdirectory(tests)

# Installation rules
install(TARGETS includer
        RUNTIME DESTINATION bin)
