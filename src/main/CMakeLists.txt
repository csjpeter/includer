
# Add executable
add_executable(includer main.cpp)

target_include_directories(includer
	PUBLIC ${CMAKE_SOURCE_DIR}/src/interfaces
	PUBLIC ${CMAKE_SOURCE_DIR}/src/main)

# Find and link cxxopts
find_package(cxxopts REQUIRED)
target_link_libraries(includer
	PRIVATE cxxopts::cxxopts
	PRIVATE applib)

# Installation rules
install(TARGETS includer
		RUNTIME DESTINATION /usr/bin)

