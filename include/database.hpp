#ifndef DATABASE_HPP_
#define DATABASE_HPP_

//#include <varargs.h>
#include <string>
#include <tableresult.hpp>
#include <sqlite3.h>
#include <log.hpp>

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
		sqlite3* db;
		sqlite3_stmt* res;
		std::string dataBaseName;
		int flags;
	public:
		Database(const char* databaseName);
		~Database();

		int Open();
		void Close();
		int BeginTran(TransactionType tranType = DEFERRED);
		int RollBack();
		int Commit();
		TableResult SelectTableAll(char* tableName);
		TableResult SelectTable(char* tableName, ...);
		long InsertIntoTable(char* tableName, std::map<std::string, std::string> columnValues);
		long UpdateTable(char* tableName, char* whereExpr, std::map<std::string, std::string> columnValues);
		long DeleteRow(char* tableName, std::string whereExpr = "");

		int ExecuteSQL(const char*);
	};
}
#endif