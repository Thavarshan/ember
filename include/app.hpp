#ifndef APP_HPP
#define APP_HPP

#include <functional>
#include <string>

#include "request.hpp"
#include "response.hpp"
#include "router.hpp"

/**
 * @namespace core
 * Namespace for core application classes and functions.
 */
namespace core {

/**
 * @class App
 * @brief Represents the application and its routes.
 *
 * This class manages the registration of routes and delegates request handling
 * to the router.
 */
class App {
 public:
  /**
   * @brief Default constructor.
   * Initializes a new instance of the App class.
   */
  App();

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
   * @brief Get the Router object
   *
   * @return router::Router&
   */
  router::Router &getRouter();

  /**
   * @brief Gets the router (const version).
   *
   * @return The router managing the routes.
   */
  const router::Router &getRouter() const;

 private:
  router::Router router;  ///< The router managing the routes.
};

}  // namespace core

#endif  // APP_HPP
