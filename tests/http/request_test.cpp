#include "request.hpp"

#include <gtest/gtest.h>

TEST(RequestTest, DefaultConstructor) {
  http::Request request;
  EXPECT_EQ(request.getMethod(), "");
  EXPECT_EQ(request.getUri(), "");
  EXPECT_EQ(request.getVersion(), "");
  EXPECT_EQ(request.getBody(), "");
  EXPECT_TRUE(request.getHeaders().empty());
}

TEST(RequestTest, ParameterizedConstructor) {
  std::map<std::string, std::string> headers = {{"Host", "www.example.com"},
                                                {"Connection", "keep-alive"}};
  http::Request request("GET", "/index.html", "HTTP/1.1", "body_content",
                        headers);
  EXPECT_EQ(request.getMethod(), "GET");
  EXPECT_EQ(request.getUri(), "/index.html");
  EXPECT_EQ(request.getVersion(), "HTTP/1.1");
  EXPECT_EQ(request.getBody(), "body_content");
  EXPECT_EQ(request.getHeader("Host"), "www.example.com");
  EXPECT_EQ(request.getHeader("Connection"), "keep-alive");
  EXPECT_TRUE(request.getHeader("Non-Existent").empty());
}

TEST(RequestTest, SettersAndGetters) {
  http::Request request;
  request.setMethod("POST");
  request.setUri("/submit");
  request.setVersion("HTTP/2.0");
  request.setBody("new_body_content");
  request.setHeader("Content-Type", "application/json");

  EXPECT_EQ(request.getMethod(), "POST");
  EXPECT_EQ(request.getUri(), "/submit");
  EXPECT_EQ(request.getVersion(), "HTTP/2.0");
  EXPECT_EQ(request.getBody(), "new_body_content");
  EXPECT_EQ(request.getHeader("Content-Type"), "application/json");
}

TEST(RequestTest, GetQueryParameters) {
  http::Request request("GET", "/search?q=example&lang=en", "HTTP/1.1", "", {});
  std::map<std::string, std::string> queryParams = request.getQueryParameters();

  EXPECT_EQ(queryParams.size(), 2);
  EXPECT_EQ(queryParams["q"], "example");
  EXPECT_EQ(queryParams["lang"], "en");
}

TEST(RequestTest, GetQueryParameter) {
  http::Request request("GET", "/search?q=example&lang=en", "HTTP/1.1", "", {});
  EXPECT_EQ(request.getQueryParameter("q"), "example");
  EXPECT_EQ(request.getQueryParameter("lang"), "en");
  EXPECT_TRUE(request.getQueryParameter("nonexistent").empty());
}

TEST(RequestTest, GetPath) {
  http::Request request("GET", "/search?q=example&lang=en", "HTTP/1.1", "", {});
  EXPECT_EQ(request.getPath(), "/search");

  http::Request requestNoQuery("GET", "/about", "HTTP/1.1", "", {});
  EXPECT_EQ(requestNoQuery.getPath(), "/about");
}

TEST(RequestTest, GetInputParameters) {
  http::Request request("POST", "/submit", "HTTP/1.1", "name=John&age=30", {});
  std::map<std::string, std::string> inputParams = request.getInputParameters();

  EXPECT_EQ(inputParams.size(), 2);
  EXPECT_EQ(inputParams["name"], "John");
  EXPECT_EQ(inputParams["age"], "30");
}

TEST(RequestTest, GetInputParameter) {
  http::Request request("POST", "/submit", "HTTP/1.1", "name=John&age=30", {});
  EXPECT_EQ(request.getInputParameter("name"), "John");
  EXPECT_EQ(request.getInputParameter("age"), "30");
  EXPECT_TRUE(request.getInputParameter("nonexistent").empty());
}

TEST(RequestTest, ParseRequest) {
  std::string rawRequest =
      "GET /index.html HTTP/1.1\r\n"
      "Host: www.example.com\r\n"
      "Connection: keep-alive\r\n"
      "\r\n"
      "body_content";

  http::Request request;
  request.parseRequest(rawRequest);

  EXPECT_EQ(request.getMethod(), "GET");
  EXPECT_EQ(request.getUri(), "/index.html");
  EXPECT_EQ(request.getVersion(), "HTTP/1.1");
  EXPECT_EQ(request.getHeader("Host"), "www.example.com");
  EXPECT_EQ(request.getHeader("Connection"), "keep-alive");
  EXPECT_EQ(request.getBody(), "body_content\n");
}

TEST(RequestTest, ToString) {
  std::map<std::string, std::string> headers = {{"Host", "www.example.com"},
                                                {"Connection", "keep-alive"}};
  http::Request request("GET", "/index.html", "HTTP/1.1", "body_content",
                        headers);

  std::string requestString = request.toString();

  EXPECT_NE(requestString.find("GET /index.html HTTP/1.1\r\n"),
            std::string::npos);
  EXPECT_NE(requestString.find("Host: www.example.com\r\n"), std::string::npos);
  EXPECT_NE(requestString.find("Connection: keep-alive\r\n"),
            std::string::npos);
  EXPECT_NE(requestString.find("\r\nbody_content"), std::string::npos);
}
