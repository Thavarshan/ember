#include "app.hpp"

#include <gtest/gtest.h>

#include "request.hpp"
#include "response.hpp"

using namespace core;
using namespace http;

TEST(AppTest, RegisterAndRetrieveRoute) {
  App app;

  // Register a route
  app.registerRoute("GET", "/home", [](const Request& request) {
    return Response(200, "OK", "Home Page", {{"Content-Type", "text/html"}});
  });

  // Check if the route is registered correctly
  auto routes = app.getRoutes();
  auto it = routes.find("GET:/home");
  ASSERT_NE(it, routes.end());
  ASSERT_EQ(it->first, "GET:/home");

  // Invoke the handler and check the response
  Request request("GET", "/home", "HTTP/1.1", "", {});
  Response response = it->second(request);
  ASSERT_EQ(response.getStatusCode(), 200);
  ASSERT_EQ(response.getStatusMessage(), "OK");
  ASSERT_EQ(response.getBody(), "Home Page");
  ASSERT_EQ(response.getHeader("Content-Type"), "text/html");
}

TEST(AppTest, RegisterMultipleRoutes) {
  App app;

  // Register multiple routes
  app.registerRoute("GET", "/home", [](const Request& request) {
    return Response(200, "OK", "Home Page", {{"Content-Type", "text/html"}});
  });
  app.registerRoute("POST", "/submit", [](const Request& request) {
    return Response(201, "Created", "Submission Received",
                    {{"Content-Type", "text/plain"}});
  });

  // Check if the routes are registered correctly
  auto routes = app.getRoutes();
  ASSERT_NE(routes.find("GET:/home"), routes.end());
  ASSERT_NE(routes.find("POST:/submit"), routes.end());

  // Invoke the handlers and check the responses
  Request getRequest("GET", "/home", "HTTP/1.1", "", {});
  Response getResponse = routes["GET:/home"](getRequest);
  ASSERT_EQ(getResponse.getStatusCode(), 200);
  ASSERT_EQ(getResponse.getStatusMessage(), "OK");
  ASSERT_EQ(getResponse.getBody(), "Home Page");
  ASSERT_EQ(getResponse.getHeader("Content-Type"), "text/html");

  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  Response postResponse = routes["POST:/submit"](postRequest);
  ASSERT_EQ(postResponse.getStatusCode(), 201);
  ASSERT_EQ(postResponse.getStatusMessage(), "Created");
  ASSERT_EQ(postResponse.getBody(), "Submission Received");
  ASSERT_EQ(postResponse.getHeader("Content-Type"), "text/plain");
}
