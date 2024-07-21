#include "route.hpp"

#include <strings.h>

#include <regex>
#include <sstream>
#include <stdexcept>

namespace router {

Route::Route(
    const std::string &method, const std::string &path,
    const std::function<http::Response(const http::Request &)> &handler)
    : method(method), path(path), handler(handler) {}

bool Route::matches(const http::Request &request) const {
  if (strcasecmp(request.getMethod().c_str(), method.c_str()) != 0) {
    return false;
  }

  std::regex pathRegex(pathToRegex(path));
  return std::regex_match(request.getUri(), pathRegex);
}

http::Response Route::handle(const http::Request &request) const {
  return handler(request);
}

std::string Route::getMethod() const { return method; }

std::string Route::getPath() const { return path; }

std::function<http::Response(const http::Request &)> Route::getHandler() const {
  return handler;
}

std::string Route::pathToRegex(const std::string &path) const {
  std::stringstream ss;
  ss << "^";
  for (char c : path) {
    if (c == ':') {
      ss << "([^/]+)";
    } else if (c == '/') {
      ss << "\\/";
    } else {
      ss << c;
    }
  }
  ss << "/?$";  // Match trailing slash optionally
  return ss.str();
}

}  // namespace router
