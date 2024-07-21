#include <iostream>

#include "app.hpp"
#include "kernel.hpp"
#include "request.hpp"
#include "response.hpp"

/**
 * @brief Main entry point of the application.
 *
 * This function serves as the starting point for program execution. It takes
 * command line arguments and can use them to influence the program's behavior.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of command line argument strings.
 *
 * @return int Returns 0 upon successful execution.
 */
int main() {
  core::App app;

  // Register a GET route
  app.registerRoute("GET", "/home", [](const http::Request &request) {
    return http::Response(200, "OK", "Welcome to the home page!",
                          {{"Content-Type", "text/plain"}});
  });

  // Register a POST route
  app.registerRoute("POST", "/submit", [](const http::Request &request) {
    return http::Response(200, "OK", "Form submitted successfully!",
                          {{"Content-Type", "text/plain"}});
  });

  core::Kernel kernel(app);

  // Create a test request
  http::Request request("GET", "/home", "HTTP/1.1", "", {});

  // Handle the request
  http::Response response = kernel.handleRequest(request);

  // Output the response
  std::cout << response.toString() << std::endl;

  return 0;
}
