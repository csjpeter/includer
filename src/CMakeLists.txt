# Add executable
add_executable(includer
				main.cpp
				CliOptions.cpp
				Processor.cpp
				FileHandler.cpp)

# Installation rules
install(TARGETS includer
        RUNTIME DESTINATION /usr/bin)
install(FILES includer.1 DESTINATION /usr/share/man/man1)

# Find and link cxxopts
find_package(cxxopts REQUIRED)
target_link_libraries(includer PRIVATE cxxopts::cxxopts)

# Debian package rules
set(CPACK_GENERATOR "DEB;RPM")
set(CPACK_PACKAGE_NAME "includer")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Peter Csaszar <csjpeter@gmail.com>")
include(CPack)

