cmake_minimum_required(VERSION 3.10)
project(UnitTests)

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)
include(GoogleTest)

# Source files for implementation
set(SOURCE_SOURCES
    ../src/CliOptions.cpp
    ../src/Processor.cpp
    # Add other source files here
)

# Source files for unit tests
set(TEST_SOURCES
    CliOptionsTests.cpp
    ProcessorTests.cpp
)

# Source files for mocks
set(MOCK_SOURCES
    mocks/MockFileHandler.hpp
)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/tests/mocks)
include_directories(${CMAKE_SOURCE_DIR}/tests)
include_directories(${CMAKE_SOURCE_DIR}/src)  # Adjust this if your source files are in a different directory

# Create the test executable
add_executable(run_tests ${TEST_SOURCES} ${MOCK_SOURCES} ${SOURCE_SOURCES})

# Link the test executable to GTest and other necessary libraries
# Find and link cxxopts
find_package(cxxopts REQUIRED)
target_link_libraries(run_tests
						cxxopts::cxxopts
						GTest::GTest
						GTest::Main)

# Add tests to CTest
gtest_discover_tests(run_tests)
