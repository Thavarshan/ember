#include "kernel.hpp"

#include <stdexcept>

#include "app.hpp"
#include "request.hpp"
#include "response.hpp"

namespace core {

Kernel::Kernel(const App &app) : app(app) {
  // Initialize the Kernel
}

http::Response Kernel::handleRequest(const http::Request &request) {
  return app.getRouter().handle(request);
}

}  // namespace core
