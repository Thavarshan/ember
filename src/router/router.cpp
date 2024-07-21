#include "router.hpp"

namespace router {

void Router::addRoute(
    const std::string &method, const std::string &path,
    const std::function<http::Response(const http::Request &)> &handler) {
  routes.emplace_back(method, path, handler);
}

http::Response Router::handle(const http::Request &request) const {
  for (const auto &route : routes) {
    if (route.matches(request)) {
      return route.handle(request);
    }
  }
  return http::Response(404, "Not Found",
                        "The requested URL was not found on this server.",
                        {{"Content-Type", "text/plain"}});
}

}  // namespace router
