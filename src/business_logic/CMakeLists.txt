
# Create a static library
add_library(applib STATIC
	Processor.cpp
	CliOptions.cpp
)

find_package(cxxopts REQUIRED)
target_link_libraries(applib PRIVATE cxxopts::cxxopts)

# Specify include directories
target_include_directories(applib PUBLIC
	${CMAKE_SOURCE_DIR}/src/interfaces
	${CMAKE_SOURCE_DIR}/src/business_logic
)

