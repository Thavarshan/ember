#include "kernel.hpp"

#include <stdexcept>

namespace core {

Kernel::Kernel(const App &app) : app(app) {
  // Initialize the Kernel
}

http::Response Kernel::handleRequest(const http::Request &request) {
  std::string routeKey = request.getMethod() + ":" + request.getUri();
  const auto &routes = app.getRoutes();
  auto it = routes.find(routeKey);
  if (it != routes.end()) {
    return it->second(request);
  } else {
    // Return a 404 Not Found response if the route is not registered
    return http::Response(404, "Not Found",
                          "The requested URL was not found on this server.",
                          {{"Content-Type", "text/plain"}});
  }
}

}  // namespace core
