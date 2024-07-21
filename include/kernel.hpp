#ifndef KERNEL_HPP
#define KERNEL_HPP

#include "app.hpp"
#include "request.hpp"
#include "response.hpp"

namespace core {

/**
 * The Kernel class serves as the central part of the application's request
 * handling mechanism. It is responsible for taking an HTTP request, processing
 * it through the application, and returning an HTTP response. The Kernel is
 * tightly coupled with the App class, which contains the application's specific
 * logic and configurations.
 */
class Kernel {
 public:
  /**
   * Constructs a Kernel object with a reference to an App instance.
   *
   * This constructor initializes the Kernel with a specific application
   * configuration and logic by taking a reference to an App object. This allows
   * the Kernel to delegate request processing to the application logic defined
   * in the App class.
   *
   * @param app A constant reference to an App instance which contains the
   * application's logic and configurations.
   */
  Kernel(const App& app);

  /**
   * Handles an incoming HTTP request and produces an HTTP response.
   *
   * This method is the core of the Kernel's functionality. It takes an HTTP
   * request as input, processes it through the application logic (as defined in
   * the App class), and returns an HTTP response. This method encapsulates the
   * entire request handling process, from receiving the request to sending back
   * a response.
   *
   * @param request A constant reference to an http::Request object representing
   * the incoming HTTP request.
   * @return An http::Response object representing the HTTP response to be sent
   * back to the client.
   */
  http::Response handleRequest(const http::Request& request);

 private:
  const App& app;  ///< A constant reference to the App instance associated with
                   ///< this Kernel. This allows the Kernel to access
                   ///< application logic and configurations.
};

}  // namespace core

#endif  // KERNEL_HPP
