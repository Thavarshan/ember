cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ember)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Include directories for SQLite3
include_directories(${SQLite3_INCLUDE_DIRS})

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SQLite3 library
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# Add Google Test
add_subdirectory(googletest)

# Enable testing
enable_testing()

# Add test source files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Create test executable
add_executable(runUnitTests ${TEST_SOURCES})

# Link test executable against gtest & gtest_main
target_link_libraries(runUnitTests gtest gtest_main ${SQLite3_LIBRARIES})

# Add tests
include(GoogleTest)
gtest_discover_tests(runUnitTests)
