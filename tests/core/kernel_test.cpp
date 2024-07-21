#include "kernel.hpp"

#include "app.hpp"
#include "gtest/gtest.h"
#include "request.hpp"
#include "response.hpp"

using namespace core;
using namespace http;

class KernelTest : public ::testing::Test {
 protected:
  App app;
  Kernel *kernel;

  void SetUp() override {
    // Initialize the App with some routes
    app.registerRoute("GET", "/home", [](const Request &request) {
      return Response(200, "OK", "Home Page", {{"Content-Type", "text/plain"}});
    });

    app.registerRoute("POST", "/submit", [](const Request &request) {
      return Response(201, "Created", "Form Submitted",
                      {{"Content-Type", "text/plain"}});
    });

    // Initialize the Kernel with the App
    kernel = new Kernel(app);
  }

  void TearDown() override {
    // Clean up the Kernel instance
    delete kernel;
  }
};

TEST_F(KernelTest, HandleRegisteredRoute) {
  Request request("GET", "/home", "HTTP/1.1", "", {});
  Response response = kernel->handleRequest(request);

  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Home Page");
  EXPECT_EQ(response.getHeader("Content-Type"), "text/plain");
}

TEST_F(KernelTest, HandleUnregisteredRoute) {
  Request request("GET", "/unknown", "HTTP/1.1", "", {});
  Response response = kernel->handleRequest(request);

  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
  EXPECT_EQ(response.getBody(),
            "The requested URL was not found on this server.");
  EXPECT_EQ(response.getHeader("Content-Type"), "text/plain");
}

TEST_F(KernelTest, HandleMultipleRoutes) {
  Request getRequest("GET", "/home", "HTTP/1.1", "", {});
  Response getResponse = kernel->handleRequest(getRequest);

  EXPECT_EQ(getResponse.getStatusCode(), 200);
  EXPECT_EQ(getResponse.getStatusMessage(), "OK");
  EXPECT_EQ(getResponse.getBody(), "Home Page");

  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  Response postResponse = kernel->handleRequest(postRequest);

  EXPECT_EQ(postResponse.getStatusCode(), 201);
  EXPECT_EQ(postResponse.getStatusMessage(), "Created");
  EXPECT_EQ(postResponse.getBody(), "Form Submitted");
}

TEST_F(KernelTest, RouteHandlerCalledWithCorrectRequest) {
  app.registerRoute("GET", "/test", [](const Request &request) {
    EXPECT_EQ(request.getMethod(), "GET");
    EXPECT_EQ(request.getUri(), "/test");
    EXPECT_EQ(request.getVersion(), "HTTP/1.1");
    EXPECT_EQ(request.getBody(), "");
    return Response(200, "OK", "Test", {{"Content-Type", "text/plain"}});
  });

  Request request("GET", "/test", "HTTP/1.1", "", {});
  Response response = kernel->handleRequest(request);

  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Test");
}
