# Ember

🔥 **Ember** is a simple C++ web framework designed for learning and experimentation. The primary goal of this project is to understand how C++ can be used in web application development, following the structure and principles inspired by the Laravel framework.

## Project Structure

```
ember/
├── CMakeLists.txt
├── LICENSE
├── README.md
├── .clang-format
├── .editorconfig
├── .gitignore
├── .gitmodules
├── build/                  # Directory for build files
├── googletest/             # Directory for Google Test framework
├── include/                # Header files
│   ├── app.hpp
│   ├── collection.hpp
│   ├── connection.hpp
│   ├── kernel.hpp
│   ├── model.hpp
│   ├── query.hpp
│   ├── request.hpp
│   ├── response.hpp
│   ├── route.hpp
│   └── router.hpp
├── lib/                    # Library files
├── scripts/                # Scripts for automation
│   └── build.sh
├── src/                    # Source files
│   ├── core/
│   │   ├── app.cpp
│   │   └── kernel.cpp
│   ├── db/
│   │   ├── connection.cpp
│   │   ├── model.cpp
│   │   └── query.cpp
│   ├── http/
│   │   ├── request.cpp
│   │   └── response.cpp
│   ├── router/
│   │   ├── collection.cpp
│   │   ├── route.cpp
│   │   └── router.cpp
│   └── main.cpp
├── tests/                  # Test files
│   ├── core/
│   │   ├── app_test.cpp
│   │   └── kernel_test.cpp
│   ├── db/
│   │   ├── connection_test.cpp
│   │   ├── model_test.cpp
│   │   └── query_test.cpp
│   ├── http/
│   │   ├── request_test.cpp
│   │   └── response_test.cpp
│   └── router/
│       ├── collection_test.cpp
│       ├── route_test.cpp
│       └── router_test.cpp
│   └── main.cpp
└── .vscode/                # VSCode configuration files
```

## Features

- **HTTP Request Handling:** Classes to handle HTTP requests.
- **HTTP Response Handling:** Classes to handle HTTP responses.
- **Object-Oriented Design:** Follows OOP principles similar to Laravel.
- **Google Test Integration:** Unit tests using Google Test framework.
- **CMake Build System:** Uses CMake for building the project.

## Requirements

- **C++17 or higher**
- **CMake 3.10 or higher**
- **SQLite3**
- **Google Test**

## Getting Started

### Clone the Repository

```sh
git clone https://github.com/yourusername/ember.git
cd ember
```

### Build and Test the Project

You can use the `build.sh` script to clean, configure, build, and test the project.

```sh
./build.sh
```

This script will:

1. Clean up old build files.
2. Configure the project with CMake.
3. Build the project.
4. Run all tests and show the results.

### Directory Structure

- **`include/`:** Contains header files for the project.
- **`src/`:** Contains source files for the project.
- **`tests/`:** Contains test files for the project.
- **`googletest/`:** Directory for Google Test framework.
- **`build/`:** Directory where build files will be generated.
- **`cleanup.sh`:** Script to clean up build files.
- **`build.sh`:** Script to build and test the project.

## Learning Objectives

The main purpose of this project is to provide a learning platform for C++ web application development. By working on this project, you will learn:

- How to structure a C++ project for web development.
- How to use CMake for managing builds.
- How to implement HTTP request and response handling.
- How to write unit tests with Google Test.
- How to follow object-oriented design principles in C++.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
