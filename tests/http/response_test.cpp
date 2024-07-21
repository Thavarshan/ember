#include "response.hpp"

#include <gtest/gtest.h>

TEST(ResponseTest, DefaultConstructor) {
  http::Response response;
  EXPECT_EQ(response.getStatusCode(), 200);
  EXPECT_EQ(response.getStatusMessage(), "OK");
  EXPECT_EQ(response.getBody(), "");
  EXPECT_TRUE(response.getHeaders().empty());
}

TEST(ResponseTest, ParameterizedConstructor) {
  std::map<std::string, std::string> headers = {
      {"Content-Type", "application/json"}, {"Connection", "keep-alive"}};
  http::Response response(404, "Not Found", "body_content", headers);
  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
  EXPECT_EQ(response.getBody(), "body_content");
  EXPECT_EQ(response.getHeader("Content-Type"), "application/json");
  EXPECT_EQ(response.getHeader("Connection"), "keep-alive");
  EXPECT_TRUE(response.getHeader("Non-Existent").empty());
}

TEST(ResponseTest, SettersAndGetters) {
  http::Response response;
  response.setStatusCode(500);
  response.setStatusMessage("Internal Server Error");
  response.setBody("error_body");
  response.setHeader("Content-Length", "123");

  EXPECT_EQ(response.getStatusCode(), 500);
  EXPECT_EQ(response.getStatusMessage(), "Internal Server Error");
  EXPECT_EQ(response.getBody(), "error_body");
  EXPECT_EQ(response.getHeader("Content-Length"), "123");
}

TEST(ResponseTest, ParseResponse) {
  std::string rawResponse =
      "HTTP/1.1 404 Not Found\r\n"
      "Content-Type: text/html\r\n"
      "Connection: close\r\n"
      "\r\n"
      "body_content";

  http::Response response;
  response.parseResponse(rawResponse);

  EXPECT_EQ(response.getStatusCode(), 404);
  EXPECT_EQ(response.getStatusMessage(), "Not Found");
  EXPECT_EQ(response.getHeader("Content-Type"), "text/html");
  EXPECT_EQ(response.getHeader("Connection"), "close");
  EXPECT_EQ(response.getBody(), "body_content\n");
}

TEST(ResponseTest, ToString) {
  std::map<std::string, std::string> headers = {
      {"Content-Type", "application/json"}, {"Connection", "keep-alive"}};
  http::Response response(200, "OK", "response_body", headers);

  std::string responseString = response.toString();

  // Check status line
  EXPECT_NE(responseString.find("HTTP/1.1 200 OK\r\n"), std::string::npos);

  // Check headers
  EXPECT_NE(responseString.find("Content-Type: application/json\r\n"),
            std::string::npos);
  EXPECT_NE(responseString.find("Connection: keep-alive\r\n"),
            std::string::npos);

  // Check body
  EXPECT_NE(responseString.find("\r\nresponse_body"), std::string::npos);
}
