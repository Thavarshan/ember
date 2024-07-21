#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <map>
#include <string>

/**
 * @namespace http
 * Namespace for HTTP related classes and functions.
 */
namespace http {

/**
 * @class Response
 * @brief Represents an HTTP response.
 *
 * This class encapsulates the details of an HTTP response, including
 * the status code, status message, headers, and body.
 */
class Response {
 public:
  /**
   * @brief Default constructor.
   * Initializes a new instance of the Response class.
   */
  Response();

  /**
   * @brief Parameterized constructor.
   * Initializes a new instance of the Response class with specified status
   * code, status message, and body.
   *
   * @param statusCode The HTTP status code of the response.
   * @param statusMessage The HTTP status message of the response.
   * @param body The body of the response.
   * @param headers The headers of the response.
   */
  Response(int statusCode, const std::string &statusMessage,
           const std::string &body,
           const std::map<std::string, std::string> &headers);

  /**
   * @brief Gets the HTTP status code of the response.
   *
   * @return The HTTP status code.
   */
  int getStatusCode() const;

  /**
   * @brief Gets the HTTP status message of the response.
   *
   * @return The HTTP status message as a string.
   */
  std::string getStatusMessage() const;

  /**
   * @brief Gets the value of a specific header from the response.
   *
   * @param key The name of the header.
   * @return The value of the header as a string. Returns an empty string if the
   * header is not found.
   */
  std::string getHeader(const std::string &key) const;

  /**
   * @brief Gets all headers from the response.
   *
   * @return A map containing all headers.
   */
  std::map<std::string, std::string> getHeaders() const;

  /**
   * @brief Gets the body of the response.
   *
   * @return The body as a string.
   */
  std::string getBody() const;

  /**
   * @brief Sets the HTTP status code of the response.
   *
   * @param statusCode The HTTP status code to set.
   */
  void setStatusCode(int statusCode);

  /**
   * @brief Sets the HTTP status message of the response.
   *
   * @param statusMessage The HTTP status message to set.
   */
  void setStatusMessage(const std::string &statusMessage);

  /**
   * @brief Sets a header in the response.
   *
   * @param key The name of the header.
   * @param value The value of the header.
   */
  void setHeader(const std::string &key, const std::string &value);

  /**
   * @brief Sets the body of the response.
   *
   * @param body The body to set.
   */
  void setBody(const std::string &body);

  /**
   * @brief Converts the Response object to a raw HTTP response string.
   *
   * @return The raw HTTP response string.
   */
  std::string toString() const;

  /**
   * @brief Parses a raw HTTP response string and populates the Response object.
   *
   * @param rawResponse The raw HTTP response string.
   */
  void parseResponse(const std::string &rawResponse);

 private:
  int statusCode;             ///< The HTTP status code of the response.
  std::string statusMessage;  ///< The HTTP status message of the response.
  std::map<std::string, std::string> headers;  ///< The headers of the response.
  std::string body;                            ///< The body of the response.
};

}  // namespace http

#endif  // HTTP_RESPONSE_HPP
