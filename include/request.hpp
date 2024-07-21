#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <map>
#include <string>

/**
 * @namespace http
 * Namespace for HTTP related classes and functions.
 */
namespace http {

/**
 * @class Request
 * @brief Represents an HTTP request.
 *
 * This class encapsulates the details of an HTTP request, including
 * the request method, URI, version, headers, and body.
 */
class Request {
 public:
  /**
   * @brief Default constructor.
   * Initializes a new instance of the Request class.
   */
  Request();

  /**
   * @brief Parameterized constructor.
   * Initializes a new instance of the Request class with specified method, URI,
   * version, body, and headers.
   *
   * @param method The HTTP method of the request.
   * @param uri The URI of the request.
   * @param version The HTTP version of the request.
   * @param body The body of the request.
   * @param headers The headers of the request.
   */
  Request(const std::string &method, const std::string &uri,
          const std::string &version, const std::string &body,
          const std::map<std::string, std::string> &headers);

  /**
   * @brief Gets the HTTP method of the request.
   *
   * @return The HTTP method as a string.
   */
  std::string getMethod() const;

  /**
   * @brief Gets the URI of the request.
   *
   * @return The URI as a string.
   */
  std::string getUri() const;

  /**
   * @brief Gets the HTTP version of the request.
   *
   * @return The HTTP version as a string.
   */
  std::string getVersion() const;

  /**
   * @brief Gets the value of a specific header from the request.
   *
   * @param key The name of the header.
   * @return The value of the header as a string. Returns an empty string if the
   * header is not found.
   */
  std::string getHeader(const std::string &key) const;

  /**
   * @brief Gets all headers from the request.
   *
   * @return A map containing all headers.
   */
  std::map<std::string, std::string> getHeaders() const;

  /**
   * @brief Gets the body of the request.
   *
   * @return The body as a string.
   */
  std::string getBody() const;

  /**
   * @brief Sets the HTTP method of the request.
   *
   * @param method The HTTP method to set.
   */
  void setMethod(const std::string &method);

  /**
   * @brief Sets the URI of the request.
   *
   * @param uri The URI to set.
   */
  void setUri(const std::string &uri);

  /**
   * @brief Sets the HTTP version of the request.
   *
   * @param version The HTTP version to set.
   */
  void setVersion(const std::string &version);

  /**
   * @brief Sets a header in the request.
   *
   * @param key The name of the header.
   * @param value The value of the header.
   */
  void setHeader(const std::string &key, const std::string &value);

  /**
   * @brief Sets the body of the request.
   *
   * @param body The body to set.
   */
  void setBody(const std::string &body);

  /**
   * @brief Get all query parameters from the URI.
   *
   * @return A map containing all query parameters.
   */
  std::map<std::string, std::string> getQueryParameters() const;

  /**
   * @brief Get a specific query parameter from the URI.
   *
   * @param key The name of the query parameter.
   * @return The value of the query parameter as a string. Returns an empty
   * string if the query parameter is not found.
   */
  std::string getQueryParameter(const std::string &key) const;

  /**
   * @brief Get the URI path without the query parameters.
   *
   * @return The URI path as a string.
   */
  std::string getPath() const;

  /**
   * @brief Get all input parameters from the body.
   *
   * @return A map containing all input parameters.
   */
  std::map<std::string, std::string> getInputParameters() const;

  /**
   * @brief Get a specific input parameter from the body.
   *
   * @param key The name of the input parameter.
   * @return The value of the input parameter as a string. Returns an empty
   * string if the input parameter is not found.
   */
  std::string getInputParameter(const std::string &key) const;

  /**
   * @brief Parses a raw HTTP request string and populates the Request object.
   *
   * @param rawRequest The raw HTTP request string.
   */
  void parseRequest(const std::string &rawRequest);

  /**
   * @brief Converts the Request object to a raw HTTP request string.
   *
   * @return The raw HTTP request string.
   */
  std::string toString() const;

 private:
  std::string method;   ///< The HTTP method of the request.
  std::string uri;      ///< The URI of the request.
  std::string version;  ///< The HTTP version of the request.
  std::string body;     ///< The body of the request.
  std::map<std::string, std::string> headers;  ///< The headers of the request.
};

}  // namespace http

#endif  // HTTP_REQUEST_HPP
