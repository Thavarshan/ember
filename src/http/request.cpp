#include "request.hpp"

#include <algorithm>
#include <sstream>

namespace http {

Request::Request() : method(""), uri(""), version(""), body("") {}

Request::Request(const std::string &method, const std::string &uri,
                 const std::string &version, const std::string &body,
                 const std::map<std::string, std::string> &headers)
    : method(method),
      uri(uri),
      version(version),
      body(body),
      headers(headers) {}

std::string Request::getMethod() const { return method; }

std::string Request::getUri() const { return uri; }

std::string Request::getVersion() const { return version; }

std::string Request::getHeader(const std::string &key) const {
  auto it = headers.find(key);
  if (it != headers.end()) {
    return it->second;
  }
  return "";
}

std::map<std::string, std::string> Request::getHeaders() const {
  return headers;
}

std::string Request::getBody() const { return body; }

void Request::setMethod(const std::string &method) { this->method = method; }

void Request::setUri(const std::string &uri) { this->uri = uri; }

void Request::setVersion(const std::string &version) {
  this->version = version;
}

void Request::setHeader(const std::string &key, const std::string &value) {
  headers[key] = value;
}

void Request::setBody(const std::string &body) { this->body = body; }

std::map<std::string, std::string> Request::getQueryParameters() const {
  std::map<std::string, std::string> queryParams;
  auto pos = uri.find('?');
  if (pos != std::string::npos) {
    std::string query = uri.substr(pos + 1);
    std::istringstream queryStream(query);
    std::string pair;
    while (std::getline(queryStream, pair, '&')) {
      auto equalsPos = pair.find('=');
      if (equalsPos != std::string::npos) {
        std::string key = pair.substr(0, equalsPos);
        std::string value = pair.substr(equalsPos + 1);
        queryParams[key] = value;
      }
    }
  }
  return queryParams;
}

std::string Request::getQueryParameter(const std::string &key) const {
  auto queryParams = getQueryParameters();
  auto it = queryParams.find(key);
  if (it != queryParams.end()) {
    return it->second;
  }
  return "";
}

std::string Request::getPath() const {
  auto pos = uri.find('?');
  if (pos != std::string::npos) {
    return uri.substr(0, pos);
  }
  return uri;
}

std::map<std::string, std::string> Request::getInputParameters() const {
  std::map<std::string, std::string> inputParams;
  std::istringstream bodyStream(body);
  std::string pair;
  while (std::getline(bodyStream, pair, '&')) {
    auto equalsPos = pair.find('=');
    if (equalsPos != std::string::npos) {
      std::string key = pair.substr(0, equalsPos);
      std::string value = pair.substr(equalsPos + 1);
      inputParams[key] = value;
    }
  }
  return inputParams;
}

std::string Request::getInputParameter(const std::string &key) const {
  auto inputParams = getInputParameters();
  auto it = inputParams.find(key);
  if (it != inputParams.end()) {
    return it->second;
  }
  return "";
}

void Request::parseRequest(const std::string &rawRequest) {
  std::istringstream stream(rawRequest);
  std::string line;

  // Parse request line
  if (std::getline(stream, line)) {
    std::istringstream lineStream(line);
    lineStream >> method >> uri >> version;
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

std::string Request::toString() const {
  std::ostringstream requestStream;
  requestStream << method << " " << uri << " " << version << "\r\n";
  // Copy headers to a vector and sort by key to ensure consistent order
  std::vector<std::pair<std::string, std::string>> sortedHeaders(
      headers.begin(), headers.end());
  std::sort(sortedHeaders.begin(), sortedHeaders.end());
  for (const auto &header : sortedHeaders) {
    requestStream << header.first << ": " << header.second << "\r\n";
  }
  requestStream << "\r\n" << body;
  return requestStream.str();
}
}  // namespace http
