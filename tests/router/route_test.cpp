#include "route.hpp"

#include <gtest/gtest.h>

#include "request.hpp"
#include "response.hpp"

using namespace http;
using namespace router;

class RouteTest : public ::testing::Test {
 protected:
  static Response sampleHandler(const Request &request) {
    return Response(200, "OK", "Sample response",
                    {{"Content-Type", "text/plain"}});
  }

  Route route = Route("GET", "/sample", sampleHandler);
};

TEST_F(RouteTest, RouteInitialization) {
  EXPECT_EQ(route.getMethod(), "GET");
  EXPECT_EQ(route.getPath(), "/sample");
}

TEST_F(RouteTest, RouteHandlerInvocation) {
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  auto response = route.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Sample response");
}

TEST_F(RouteTest, DifferentMethodsSamePath) {
  Route postRoute("POST", "/sample", sampleHandler);
  Request postRequest("POST", "/sample", "HTTP/1.1", "", {});
  auto response = postRoute.handle(postRequest);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(RouteTest, PathParameters) {
  Route paramRoute("GET", "/item/:id", sampleHandler);
  Request request("GET", "/item/1", "HTTP/1.1", "", {});
  auto response = paramRoute.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(RouteTest, QueryParameters) {
  Request request("GET", "/sample?query=test", "HTTP/1.1", "", {});
  auto response = route.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(RouteTest, BodyParameters) {
  Route postRoute("POST", "/submit", sampleHandler);
  Request request("POST", "/submit", "HTTP/1.1", "body=data", {});
  auto response = postRoute.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(RouteTest, InvalidMethod) {
  Request request("POST", "/sample", "HTTP/1.1", "", {});
  auto response = route.handle(request);
  EXPECT_EQ(response.getStatusCode(), 405);
  EXPECT_EQ(response.getStatusMessage(), "Method Not Allowed");
}
