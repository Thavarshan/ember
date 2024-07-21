#!/bin/bash

# Function to clean up the build directory
cleanup() {
  echo "Cleaning up old build files..."
  rm -rf build
  mkdir build
}

# Function to configure CMake
configure() {
  echo "Configuring CMake..."
  cd build
  cmake ..
}

# Function to build the project
build() {
  echo "Building the project..."
  cmake --build .
}

# Function to run tests
run_tests() {
  echo "Running tests..."
  ctest --output-on-failure
}

# Main function to orchestrate the build process
main() {
  cleanup
  configure
  build
  run_tests
  echo "Build and test process completed."
}

# Execute the main function
main
