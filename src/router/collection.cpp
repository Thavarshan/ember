#include "collection.hpp"

#include <algorithm>
#include <stdexcept>

namespace router {

void Collection::addRoute(
    const std::string &method, const std::string &path,
    const std::function<http::Response(const http::Request &)> &handler) {
  routes.emplace_back(method, path, handler);
}

const Route &Collection::getRoute(const std::string &method,
                                  const std::string &path) const {
  for (const auto &route : routes) {
    if (route.getMethod() == method && route.getPath() == path) {
      return route;
    }
  }
  throw std::runtime_error("Route not found");
}

http::Response Collection::handleRequest(const http::Request &request) const {
  for (const auto &route : routes) {
    if (route.matches(request)) {
      return route.handle(request);
    }
  }
  return http::Response(404, "Not Found",
                        "The requested URL was not found on this server.",
                        {{"Content-Type", "text/plain"}});
}

void Collection::removeRoute(const std::string &method,
                             const std::string &path) {
  routes.erase(std::remove_if(routes.begin(), routes.end(),
                              [&method, &path](const Route &route) {
                                return route.getMethod() == method &&
                                       route.getPath() == path;
                              }),
               routes.end());
}

}  // namespace router
