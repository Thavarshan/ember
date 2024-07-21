#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "request.hpp"
#include "response.hpp"
#include "route.hpp"

namespace router {

/**
 * The Router class is responsible for managing all routes within the
 * application. It provides mechanisms to add routes and to handle incoming HTTP
 * requests by routing them to the appropriate handler based on the request's
 * method and path.
 */
class Router {
 public:
  /**
   * Adds a new route to the router.
   *
   * This method allows for the registration of a new route by specifying the
   * HTTP method, the path, and a handler function. The handler function is
   * expected to take an http::Request object as input and return an
   * http::Response object.
   *
   * @param method The HTTP method (e.g., GET, POST) associated with the route.
   * @param path The path pattern (e.g., "/users/:userId") associated with the
   * route.
   * @param handler A function that handles the request and produces a response.
   */
  void addRoute(
      const std::string &method, const std::string &path,
      const std::function<http::Response(const http::Request &)> &handler);

  /**
   * Handles an incoming HTTP request by routing it to the appropriate handler.
   *
   * This method iterates through all registered routes and attempts to find a
   * match based on the request's method and path. If a match is found, the
   * corresponding handler is invoked, and its response is returned. If no match
   * is found, a default 404 Not Found response is returned.
   *
   * @param request The incoming HTTP request to be handled.
   * @return An http::Response object representing the response to the request.
   */
  http::Response handle(const http::Request &request) const;

 private:
  std::vector<router::Route>
      routes;  ///< A vector of all routes registered with the router.
};

}  // namespace router

#endif  // ROUTER_HPP
