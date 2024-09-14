# Add executable
add_executable(includer
				main.cpp
				CliOptions.cpp
				Processor.cpp
				FileHandler.cpp)

# Installation rules
install(TARGETS includer
        RUNTIME DESTINATION /usr/bin)

# Find and link cxxopts
find_package(cxxopts REQUIRED)
target_link_libraries(includer PRIVATE cxxopts::cxxopts)

