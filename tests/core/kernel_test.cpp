#include "kernel.hpp"

#include <gtest/gtest.h>

#include "app.hpp"
#include "request.hpp"
#include "response.hpp"

using namespace core;
using namespace http;

TEST(KernelTest, HandleRegisteredRoute) {
  App app;
  Kernel kernel(app);

  // Register a route
  app.registerRoute("GET", "/home", [](const Request& request) {
    return Response(200, "OK", "Welcome Home",
                    {{"Content-Type", "text/plain"}});
  });

  // Create a request and handle it
  Request request("GET", "/home", "HTTP/1.1", "", {});
  Response response = kernel.handleRequest(request);

  // Check the response
  ASSERT_EQ(response.getStatusCode(), 200);
  ASSERT_EQ(response.getStatusMessage(), "OK");
  ASSERT_EQ(response.getBody(), "Welcome Home");
  ASSERT_EQ(response.getHeader("Content-Type"), "text/plain");
}

TEST(KernelTest, HandleUnregisteredRoute) {
  App app;
  Kernel kernel(app);

  // Create a request for an unregistered route
  Request request("GET", "/unknown", "HTTP/1.1", "", {});
  Response response = kernel.handleRequest(request);

  // Check the response (should be 404 Not Found)
  ASSERT_EQ(response.getStatusCode(), 404);
  ASSERT_EQ(response.getStatusMessage(), "Not Found");
  ASSERT_EQ(response.getBody(),
            "The requested URL was not found on this server.");
  ASSERT_EQ(response.getHeader("Content-Type"), "text/plain");
}

TEST(KernelTest, HandleMultipleRoutes) {
  App app;
  Kernel kernel(app);

  // Register multiple routes
  app.registerRoute("GET", "/home", [](const Request& request) {
    return Response(200, "OK", "Welcome Home",
                    {{"Content-Type", "text/plain"}});
  });
  app.registerRoute("POST", "/submit", [](const Request& request) {
    return Response(201, "Created", "Submission Successful",
                    {{"Content-Type", "text/plain"}});
  });

  // Handle GET request
  Request getRequest("GET", "/home", "HTTP/1.1", "", {});
  Response getResponse = kernel.handleRequest(getRequest);
  ASSERT_EQ(getResponse.getStatusCode(), 200);
  ASSERT_EQ(getResponse.getStatusMessage(), "OK");
  ASSERT_EQ(getResponse.getBody(), "Welcome Home");
  ASSERT_EQ(getResponse.getHeader("Content-Type"), "text/plain");

  // Handle POST request
  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  Response postResponse = kernel.handleRequest(postRequest);
  ASSERT_EQ(postResponse.getStatusCode(), 201);
  ASSERT_EQ(postResponse.getStatusMessage(), "Created");
  ASSERT_EQ(postResponse.getBody(), "Submission Successful");
  ASSERT_EQ(postResponse.getHeader("Content-Type"), "text/plain");
}
