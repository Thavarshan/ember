#include "app.hpp"

#include <functional>
#include <string>

#include "request.hpp"
#include "response.hpp"
#include "route.hpp"
#include "router.hpp"

namespace core {

App::App() {
  // Initialize the App if necessary
}

void App::registerRoute(
    const std::string &method, const std::string &path,
    const std::function<http::Response(const http::Request &)> &handler) {
  router.addRoute(method, path, handler);
}

router::Router &App::getRouter() { return router; }

const router::Router &App::getRouter() const { return router; }

}  // namespace core
