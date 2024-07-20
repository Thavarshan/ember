#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <sqlite3.h>

/**
 * @brief Represents a connection to a SQLite database.
 *
 * This class provides an abstraction over the sqlite3* handle, managing
 * the lifetime of the connection to the database. It allows for opening
 * and closing the database connection in a RAII manner.
 */
class Connection
{
public:
  /**
   * @brief Constructs a new Connection object and opens a connection to the specified database.
   *
   * @param db_path The path to the database file.
   *
   * @throw std::runtime_error if the database connection fails to open.
   */
  Connection(const std::string &db_path);

  /**
   * @brief Destroys the Connection object, ensuring the database connection is closed properly.
   */
  ~Connection();

  /**
   * @brief Gets the underlying sqlite3* database handle.
   *
   * @return sqlite3* The sqlite3 database handle.
   */
  sqlite3 *get_db() const;

private:
  /**
   * @brief The sqlite3 database handle.
   */
  sqlite3 *db;
};

#endif // CONNECTION_HPP
