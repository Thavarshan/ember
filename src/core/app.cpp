#include "app.hpp"

namespace core {

void App::registerRoute(
    const std::string &method, const std::string &path,
    const std::function<http::Response(const http::Request &)> &handler) {
  std::string routeKey = method + ":" + path;
  routes[routeKey] = handler;
}

const std::map<std::string,
               std::function<http::Response(const http::Request &)>> &
App::getRoutes() const {
  return routes;
}

}  // namespace core
