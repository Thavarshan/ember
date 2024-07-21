#include "collection.hpp"

#include <gtest/gtest.h>

#include "request.hpp"
#include "response.hpp"

using namespace http;
using namespace router;

class CollectionTest : public ::testing::Test {
 protected:
  Collection collection;

  static Response sampleHandler(const Request &request) {
    return Response(200, "OK", "Sample response",
                    {{"Content-Type", "text/plain"}});
  }

  void SetUp() override {
    collection.addRoute("GET", "/sample", sampleHandler);
  }
};

TEST_F(CollectionTest, AddAndRetrieveRoute) {
  const auto &route = collection.getRoute("GET", "/sample");
  EXPECT_EQ(route.getMethod(), "GET");
  EXPECT_EQ(route.getPath(), "/sample");
}

TEST_F(CollectionTest, HandleRequestToExistingRoute) {
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "Sample response");
}

TEST_F(CollectionTest, HandleRequestToNonExistentRoute) {
  Request request("GET", "/nonexistent", "HTTP/1.1", "", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
}

TEST_F(CollectionTest, HandleMultipleRoutes) {
  collection.addRoute("POST", "/submit", sampleHandler);

  Request getRequest("GET", "/sample", "HTTP/1.1", "", {});
  auto getResponse = collection.handleRequest(getRequest);
  EXPECT_EQ(getResponse.getStatusCode(), 200);
  EXPECT_EQ(getResponse.getStatusMessage(), "OK");

  Request postRequest("POST", "/submit", "HTTP/1.1", "", {});
  auto postResponse = collection.handleRequest(postRequest);
  EXPECT_EQ(postResponse.getStatusCode(), 200);
  EXPECT_EQ(postResponse.getStatusMessage(), "OK");
}

TEST_F(CollectionTest, HandleRequestWithPathParameters) {
  collection.addRoute("GET", "/item/:id", sampleHandler);

  Request request("GET", "/item/1", "HTTP/1.1", "", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(CollectionTest, HandleRequestWithQueryParameters) {
  Request request("GET", "/sample?query=test", "HTTP/1.1", "", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(CollectionTest, HandleRequestWithBodyParameters) {
  collection.addRoute("POST", "/submit", sampleHandler);

  Request request("POST", "/submit", "HTTP/1.1", "body=data", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
}

TEST_F(CollectionTest, RemoveRoute) {
  collection.removeRoute("GET", "/sample");
  Request request("GET", "/sample", "HTTP/1.1", "", {});
  auto response = collection.handleRequest(request);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
}
