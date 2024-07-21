#include "router.hpp"

#include <gtest/gtest.h>

#include "request.hpp"
#include "response.hpp"

using namespace http;
using namespace router;

class RouterTest : public ::testing::Test {
 protected:
  static Response sampleHandler(const Request &request) {
    return Response(200, "OK", "GET response",
                    {{"Content-Type", "text/plain"}});
  }

  static Response postHandler(const Request &request) {
    return Response(200, "OK", "POST response",
                    {{"Content-Type", "text/plain"}});
  }

  Router router;
};

TEST_F(RouterTest, AddAndHandleSingleRoute) {
  router.addRoute("GET", "/sample", sampleHandler);
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  auto response = router.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "GET response");
}

TEST_F(RouterTest, HandleNotFoundRoute) {
  Request request("GET", "/nonexistent", "HTTP/1.1", "", {});
  auto response = router.handle(request);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
}

TEST_F(RouterTest, AddAndHandleMultipleRoutes) {
  router.addRoute("GET", "/sample", sampleHandler);
  router.addRoute("POST", "/submit", postHandler);

  Request getRequest("GET", "/sample", "HTTP/1.1", "", {});
  auto getResponse = router.handle(getRequest);
  EXPECT_EQ(getResponse.getStatusCode(), 200);
  EXPECT_EQ(getResponse.getStatusMessage(), "OK");
  EXPECT_EQ(getResponse.getBody(), "GET response");

  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  auto postResponse = router.handle(postRequest);
  EXPECT_EQ(postResponse.getStatusCode(), 200);
  EXPECT_EQ(postResponse.getStatusMessage(), "OK");
  EXPECT_EQ(postResponse.getBody(), "POST response");
}

TEST_F(RouterTest, HandleDifferentMethodsSamePath) {
  router.addRoute("GET", "/sample", sampleHandler);
  router.addRoute("POST", "/sample", postHandler);

  Request getRequest("GET", "/sample", "HTTP/1.1", "", {});
  auto getResponse = router.handle(getRequest);
  EXPECT_EQ(getResponse.getStatusCode(), 200);
  EXPECT_EQ(getResponse.getStatusMessage(), "OK");
  EXPECT_EQ(getResponse.getBody(), "GET response");

  Request postRequest("POST", "/sample", "HTTP/1.1", "", {});
  auto postResponse = router.handle(postRequest);
  EXPECT_EQ(postResponse.getStatusCode(), 200);
  EXPECT_EQ(postResponse.getStatusMessage(), "OK");
  EXPECT_EQ(postResponse.getBody(), "POST response");
}

TEST_F(RouterTest, NoRoutesConfigured) {
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  auto response = router.handle(request);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
}

TEST_F(RouterTest, CaseInsensitiveMethod) {
  router.addRoute("GET", "/sample", sampleHandler);
  Request request("get", "/sample", "HTTP/1.1", "", {});
  auto response = router.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "GET response");
}

TEST_F(RouterTest, TrailingSlash) {
  router.addRoute("GET", "/sample", sampleHandler);
  Request request("GET", "/sample/", "HTTP/1.1", "", {});
  auto response = router.handle(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "GET response");
}
