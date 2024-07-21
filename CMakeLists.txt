cmake_minimum_required(VERSION 3.10)

# Set the project name
project(ember)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find SQLite3
find_package(SQLite3 REQUIRED)

# Include directories for SQLite3
include_directories(${SQLite3_INCLUDE_DIRS})

# Source files for the main executable, excluding main.cpp
file(GLOB_RECURSE MAIN_SOURCES "src/*.cpp")
list(REMOVE_ITEM MAIN_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# Add the main executable
add_executable(${PROJECT_NAME} ${MAIN_SOURCES} src/main.cpp)

# Link SQLite3 library
target_link_libraries(${PROJECT_NAME} ${SQLite3_LIBRARIES})

# Add Google Test
add_subdirectory(googletest)

# Enable testing
enable_testing()

# Add test source files
file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

# Add the implementation files needed for tests, excluding main.cpp
file(GLOB_RECURSE TEST_IMPLEMENTATION_SOURCES "src/*.cpp")
list(REMOVE_ITEM TEST_IMPLEMENTATION_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

# Create test executable with unified main.cpp
add_executable(runUnitTests tests/main.cpp ${TEST_SOURCES} ${TEST_IMPLEMENTATION_SOURCES})

# Link test executable against gtest & gtest_main and SQLite3 libraries
target_link_libraries(runUnitTests gtest gtest_main ${SQLite3_LIBRARIES})

# Add tests
include(GoogleTest)
gtest_discover_tests(runUnitTests)

# Ensure that tests are discovered and run
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
