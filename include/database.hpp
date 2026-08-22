#ifndef DATABASE_HPP_
#define DATABASE_HPP_
#include <log.hpp>
#include <string>
#include <tableresult.hpp>

// Forward declaring to avoid clients having to include sqlite3.h themselves
struct sqlite3;
struct sqlite3_stmt;

namespace sqlite3_orm
{
enum TransactionType
{
    DEFERRED,
    IMMEDIATE,
    EXCLUSIVE
};

class Database
{
    sqlite3 *db;
    sqlite3_stmt *res;
    std::string dataBaseName;
    int flags;

  public:
    Database(const char *databaseName);
    ~Database();

    int Open();
    void Close();
    int BeginTran(TransactionType tranType = DEFERRED);
    int RollBack();
    int Commit();
    TableResult SelectTableAll(const char *tableName);
    TableResult SelectTable(char *tableName, ...);
    long InsertIntoTable(const char *tableName, std::map<std::string, std::string> columnValues);
    long UpdateTable(const char *tableName, const char *whereExpr, std::map<std::string, std::string> columnValues);
    long DeleteRow(const char *tableName, std::string whereExpr = "");

    int ExecuteSQL(const char *);
};
} // namespace sqlite3_orm
#endif
