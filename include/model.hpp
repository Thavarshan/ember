#ifndef MODEL_HPP
#define MODEL_HPP

#include "connection.hpp"
#include <string>
#include <vector>
#include <map>
#include <any>
#include <functional>

/**
 * @brief Base class for database models.
 *
 * This class provides common functionality for database models, including
 * CRUD operations and querying. Specific models should inherit from this class
 * and implement their own specific behavior.
 */
class Model {
public:
    /**
     * @brief Constructs a new Model object.
     *
     * @param table_name The name of the table associated with the model.
     * @param connection A reference to a Connection object.
     */
    Model(const std::string& table_name, Connection& connection);

    /**
     * @brief Creates a new record in the database.
     *
     * @param attributes A map of column names to values for the new record.
     * @return true If the record was successfully created.
     * @return false If the record could not be created.
     */
    bool create(const std::map<std::string, std::any>& attributes);

    /**
     * @brief Updates an existing record in the database.
     *
     * @param id The ID of the record to update.
     * @param attributes A map of column names to new values for the record.
     * @return true If the record was successfully updated.
     * @return false If the record could not be updated.
     */
    bool update(int id, const std::map<std::string, std::any>& attributes);

    /**
     * @brief Deletes a record from the database by ID.
     *
     * @param id The ID of the record to delete.
     * @return true If the record was successfully deleted.
     * @return false If the record could not be deleted.
     */
    bool remove(int id);

    /**
     * @brief Finds a record by ID.
     *
     * @param id The ID of the record to find.
     * @return std::map<std::string, std::any> A map of column names to values for the found record.
     */
    std::map<std::string, std::any> find(int id);

    /**
     * @brief Retrieves all records from the table.
     *
     * @return std::vector<std::map<std::string, std::any>> A vector of maps, each representing a record.
     */
    std::vector<std::map<std::string, std::any>> all();

    /**
     * @brief Performs a query to find records matching a specific condition.
     *
     * @param column The column to match against.
     * @param value The value to match in the specified column.
     * @return std::vector<std::map<std::string, std::any>> A vector of maps, each representing a record that matches the condition.
     */
    std::vector<std::map<std::string, std::any>> where(const std::string& column, const std::string& value);

    /**
     * @brief Performs a query to find records matching a specific condition with an operator.
     *
     * @param column The column to match against.
     * @param op The operator to use in the match (e.g., '=', '>', '<').
     * @param value The value to match in the specified column.
     * @return std::vector<std::map<std::string, std::any>> A vector of maps, each representing a record that matches the condition.
     */
    std::vector<std::map<std::string, std::any>> where(const std::string& column, const std::string& op, const std::string& value);

    /**
     * @brief Retrieves all records that match the previously specified query conditions.
     *
     * @return std::vector<std::map<std::string, std::any>> A vector of maps, each representing a record that matches the query conditions.
     */
    std::vector<std::map<std::string, std::any>> get();

protected:
    /**
     * @brief The connection to the database.
     */
    Connection& connection;

    /**
     * @brief The name of the table associated with the model.
     */
    std::string table_name;

    /**
     * @brief Executes a SQL query without a callback.
     *
     * @param query The SQL query to execute.
     * @return true If the query was successfully executed.
     * @return false If the query failed to execute.
     */
    bool execute_query(const std::string& query);

    /**
     * @brief Executes a SQL query with a callback function.
     *
     * @param query The SQL query to execute.
     * @param callback The callback function to process each row of the result set.
     * @param data User-defined data to pass to the callback function.
     * @return true If the query was successfully executed.
     * @return false If the query failed to execute.
     */
    bool execute_query(const std::string& query, int (*callback)(void*, int, char**, char**), void* data);

    /**
     * @brief Callback function for processing SQL query results.
     *
     * @param data User-defined data.
     * @param argc The number of columns in the result.
     * @param argv The values of each column in the current row.
     * @param colNames The names of each column.
     * @return int A status code.
     */
    static int query_callback(void* data, int argc, char** argv, char** colNames);

    /**
     * @brief Escapes a string to prevent SQL injection.
     *
     * @param input The string to escape.
     * @return std::string The escaped string.
     */
    std::string escape_string(const std::string& input);
};

#endif // MODEL_HPP
