cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Ember)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(Ember ${SOURCES})

# Add testing
enable_testing()

# Tests
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")
add_executable(runUnitTests ${TEST_SOURCES})
add_test(NAME runUnitTests COMMAND runUnitTests)
