cmake_minimum_required(VERSION 3.10)
project(includer VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

include(CTest)
add_subdirectory(tests)

add_subdirectory(man)

# Installation rules
install(TARGETS includer RUNTIME DESTINATION bin)

# Debian package rules
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_PACKAGE_NAME "includer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Peter Csaszar <csjpeter@gmail.com>")
include(CPack)
