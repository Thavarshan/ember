#include "response.hpp"

#include <algorithm>
#include <sstream>
#include <vector>

namespace http {

Response::Response() : statusCode(200), statusMessage("OK"), body("") {}

Response::Response(int statusCode, const std::string &statusMessage,
                   const std::string &body,
                   const std::map<std::string, std::string> &headers)
    : statusCode(statusCode),
      statusMessage(statusMessage),
      body(body),
      headers(headers) {}

int Response::getStatusCode() const { return statusCode; }

std::string Response::getStatusMessage() const { return statusMessage; }

std::string Response::getHeader(const std::string &key) const {
  auto it = headers.find(key);
  if (it != headers.end()) {
    return it->second;
  }
  return "";
}

std::map<std::string, std::string> Response::getHeaders() const {
  return headers;
}

std::string Response::getBody() const { return body; }

void Response::setStatusCode(int statusCode) { this->statusCode = statusCode; }

void Response::setStatusMessage(const std::string &statusMessage) {
  this->statusMessage = statusMessage;
}

void Response::setHeader(const std::string &key, const std::string &value) {
  headers[key] = value;
}

void Response::setBody(const std::string &body) { this->body = body; }

void Response::parseResponse(const std::string &rawResponse) {
  std::istringstream stream(rawResponse);
  std::string line;

  // Parse status line
  if (std::getline(stream, line)) {
    std::istringstream lineStream(line);
    std::string httpVersion;
    lineStream >> httpVersion >> statusCode;
    std::getline(lineStream, statusMessage);
    if (!statusMessage.empty() && statusMessage[0] == ' ') {
      statusMessage.erase(0, 1);  // Remove leading space
    }
    if (!statusMessage.empty() && statusMessage.back() == '\r') {
      statusMessage.pop_back();  // Remove trailing '\r'
    }
  }

  // Parse headers
  while (std::getline(stream, line) && line != "\r") {
    if (line.back() == '\r') {
      line.pop_back();  // Remove the trailing '\r'
    }
    std::size_t delimiterPosition = line.find(": ");
    if (delimiterPosition != std::string::npos) {
      std::string key = line.substr(0, delimiterPosition);
      std::string value = line.substr(delimiterPosition + 2);
      headers[key] = value;
    }
  }

  // Parse body
  std::stringstream bodyStream;
  while (std::getline(stream, line)) {
    bodyStream << line << "\n";
  }
  body = bodyStream.str();
}

std::string Response::toString() const {
  std::ostringstream responseStream;
  responseStream << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
  // Copy headers to a vector and sort by key to ensure consistent order
  std::vector<std::pair<std::string, std::string>> sortedHeaders(
      headers.begin(), headers.end());
  std::sort(sortedHeaders.begin(), sortedHeaders.end());
  for (const auto &header : sortedHeaders) {
    responseStream << header.first << ": " << header.second << "\r\n";
  }
  responseStream << "\r\n" << body;
  return responseStream.str();
}

}  // namespace http
