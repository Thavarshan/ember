#ifndef APP_HPP
#define APP_HPP

#include <functional>
#include <map>
#include <string>

#include "request.hpp"
#include "response.hpp"

/**
 * @namespace core
 * Namespace for core application classes and functions.
 */
namespace core {

class App {
 public:
  /**
   * @brief Registers a route with a corresponding handler.
   *
   * @param method The HTTP method (e.g., GET, POST).
   * @param path The path for the route (e.g., /home).
   * @param handler The handler function for the route.
   */
  void registerRoute(
      const std::string &method, const std::string &path,
      const std::function<http::Response(const http::Request &)> &handler);

  /**
   * @brief Gets the registered routes.
   *
   * @return A map of routes to their handlers.
   */
  const std::map<std::string,
                 std::function<http::Response(const http::Request &)>> &
  getRoutes() const;

 private:
  std::map<std::string, std::function<http::Response(const http::Request &)>>
      routes;  ///< Map of routes to their handlers.
};

}  // namespace core

#endif  // APP_HPP
