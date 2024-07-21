#include "connection.hpp"

#include <iostream>
#include <stdexcept>

Connection::Connection(const std::string &db_path) {
  int result = sqlite3_open(db_path.c_str(), &db);

  if (result != SQLITE_OK) {
    throw std::runtime_error("Failed to open database: " +
                             std::string(sqlite3_errmsg(db)));
  }
}

Connection::~Connection() { sqlite3_close(db); }

sqlite3 *Connection::get_db() const { return db; }
