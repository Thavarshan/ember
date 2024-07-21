#include "app.hpp"

#include <gtest/gtest.h>

#include "request.hpp"
#include "response.hpp"
#include "router.hpp"

using namespace http;
using namespace router;
using namespace core;

class AppTest : public ::testing::Test {
 protected:
  core::App app;

  static Response sampleHandler(const Request &request) {
    return Response(200, "OK", "Sample response",
                    {{"Content-Type", "text/plain"}});
  }

  void SetUp() override {
    app.getRouter().addRoute("GET", "/sample", sampleHandler);
  }
};

TEST_F(AppTest, RegisterAndRetrieveRoute) {
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  Response response = app.getRouter().handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Sample response");
}

TEST_F(AppTest, RegisterMultipleRoutes) {
  app.getRouter().addRoute("POST", "/submit", [](const Request &request) {
    return Response(200, "OK", "POST response",
                    {{"Content-Type", "text/plain"}});
  });

  Request getRequest("GET", "/sample", "HTTP/1.1", "", {});
  Response getResponse = app.getRouter().handle(getRequest);
  EXPECT_EQ(getResponse.getStatusCode(), 200);
  EXPECT_EQ(getResponse.getStatusMessage(), "OK");
  EXPECT_EQ(getResponse.getBody(), "Sample response");

  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  Response postResponse = app.getRouter().handle(postRequest);
  EXPECT_EQ(postResponse.getStatusCode(), 200);
  EXPECT_EQ(postResponse.getStatusMessage(), "OK");
  EXPECT_EQ(postResponse.getBody(), "POST response");
}

TEST_F(AppTest, HandleUnknownRoute) {
  Request request("GET", "/unknown", "HTTP/1.1", "", {});
  Response response = app.getRouter().handle(request);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
}

TEST_F(AppTest, RouteHandlerCalledWithCorrectRequest) {
  bool handlerCalled = false;
  app.getRouter().addRoute("GET", "/test",
                           [&handlerCalled](const Request &request) {
                             handlerCalled = true;
                             return Response(200, "OK", "Test response",
                                             {{"Content-Type", "text/plain"}});
                           });

  Request request("GET", "/test", "HTTP/1.1", "", {});
  Response response = app.getRouter().handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Test response");
  EXPECT_TRUE(handlerCalled);
}
