#include<database.hpp>
#include<sqlite3.h>
#include<constants.hpp>

namespace sqlite3_orm
{
	Database::Database(const char* databaseName)
	{
		Log::info("database constructor");
		Log::info(databaseName);

		this->dataBaseName = databaseName;
	}

	Database::~Database()
	{
		Log::info("Destructor");
	}

	int Database::Open()
	{
		Log::info("Openning database");

		int rc = sqlite3_open(dataBaseName.c_str(), &db);
		if (rc != SQLITE_OK)
		{
			Log::error("Couldn't open database");
			Log::error(sqlite3_errmsg(db));
			sqlite3_close(db);
			return -1;
		}

		Log::info("Opened database");
		return rc;
	}

	void Database::Close()
	{
		Log::info("Closing database");
		sqlite3_close(db);
		Log::info("Closed database");
	}

	int Database::BeginTran(TransactionType tranType)
	{
		std::string result;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result += "BEGIN ";

		switch (tranType)
		{
		case sqlite3_orm::DEFERRED:
			result += "DEFERRED ";
			break;
		case sqlite3_orm::IMMEDIATE:
			result += "IMMEDIATE ";
			break;
		case sqlite3_orm::EXCLUSIVE:
			result += "EXCLUSIVE ";
			break;
		default:
			break;
		}

		result += "TRANSACTION";

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_free(errMsg);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rc : rowChanged;
	}

	int Database::RollBack()
	{
		std::string result;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result += "ROLLBACK TRANSACTION";

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_free(errMsg);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rc : rowChanged;
	}

	int Database::Commit()
	{
		std::string result;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result += "COMMIT TRANSACTION";

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_free(errMsg);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rc : rowChanged;
	}

	TableResult Database::SelectTableAll(char* tableName)
	{
		TableResult tableResult(tableName);
		std::vector<std::string> rowFields;
		std::vector<std::string> rowHeaders;
		std::string columnName;
		std::string result;
		sqlite3_stmt* statement;
		char** pargs = &tableName;
		char* nextArg = NULL;
		int rc;

		Log::info("SelectTableAll");

		result.assign("SELECT * FROM ");
		result.append(tableName);

		Log::debug(result.c_str());

		rc = sqlite3_prepare_v2(db, result.c_str(), -1, &statement, 0);
		tableResult.setSqliteResult(rc);

		if (rc != SQLITE_OK)
		{
			Log::error(sqlite3_errmsg(db));
			sqlite3_finalize(statement);
			return tableResult;
		}

		for (size_t i = 0; i < sqlite3_column_count(statement); i++)
		{
			Log::debug((const char*)sqlite3_column_name(statement, i));
			rowHeaders.push_back((char*)sqlite3_column_name(statement, i));
		}

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			rowFields.clear();
			for (size_t i = 0; i < sqlite3_column_count(statement); i++)
			{
				Log::debug((const char*)sqlite3_column_text(statement, i));
				rowFields.push_back((char*)sqlite3_column_text(statement, i));
			}
			tableResult.addRow(rowHeaders, rowFields);
		}

		Log::info("sqlite3_finalize");
		sqlite3_finalize(statement);

		return tableResult;
	}


	TableResult Database::SelectTable(char* tableName, ...)
	{
		TableResult tableResult(tableName);
		std::vector<std::string> rowFields;
		std::vector<std::string> rowHeaders;
		std::string columnName;
		std::string result;
		sqlite3_stmt* statement;
		char** pargs = &tableName;
		char* nextArg = NULL;
		int rc;

		Log::info("SelectTable");

		result += "SELECT ";

		for (nextArg = *(++pargs);
			nextArg != NULL;
			nextArg = *(pargs++))
		{
			if (*pargs == NULL) break;
			nextArg = *pargs;
			rowHeaders.push_back(nextArg);
			result += nextArg;
			if (*(pargs + 1) != NULL)
				result += ",";
		}

		if (rowHeaders.size() <= 0)
		{
			result.assign("SELECT *");
		}

		result += " FROM " + std::string(tableName);

		Log::debug(result.c_str());

		rc = sqlite3_prepare_v2(db, result.c_str(), -1, &statement, 0);
		tableResult.setSqliteResult(rc);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_finalize(statement);
			return tableResult;
		}

		while (sqlite3_step(statement) == SQLITE_ROW)
		{
			rowFields.clear();
			for (size_t i = 0; i < sqlite3_column_count(statement); i++)
			{
				Log::debug((const char*)sqlite3_column_text(statement, i));
				rowFields.push_back((char*)sqlite3_column_text(statement, i));
			}
			tableResult.addRow(rowHeaders, rowFields);
		}

		Log::info("sqlite3_finalize");
		sqlite3_finalize(statement);

		return tableResult;
	}

	long Database::InsertIntoTable(char* tableName, std::map<std::string, std::string> columnValues)
	{
		std::vector<std::string> rowFields;
		std::vector<std::string> rowHeaders;
		std::string columnName;
		std::string result;
		//sqlite3_stmt* statement;
		char** pargs = &tableName;
		char* nextArg = NULL;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result += "INSERT INTO " + std::string(tableName) + "(";

		for (std::map<std::string, std::string>::iterator it = columnValues.begin();
			it != columnValues.end();
			it++)
		{
			std::pair<std::string, std::string> par = *it;
			Log::debug(par.first.c_str());
			result += par.first;

			std::map<std::string, std::string>::iterator temp = it;
			temp++;
			if (temp != columnValues.end())
				result += ",";
		}

		result += ") VALUES (";

		for (std::map<std::string, std::string>::iterator it = columnValues.begin();
			it != columnValues.end();
			it++)
		{
			result += it->second;
			Log::debug(it->second.c_str());
			std::map<std::string, std::string>::iterator temp = it;
			temp++;
			if (temp != columnValues.end())
				result += ",";
		}

		result += ")";

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			if (errMsg != NULL)
				Log::error(errMsg);
			else
				Log::error("Error desconocido sin mensaje");
			sqlite3_free(errMsg);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rowChanged : rc;
	}

	long Database::UpdateTable(char* tableName, char* whereExpr, std::map<std::string, std::string> columnValues)
	{
		std::vector<std::string> rowFields;
		std::vector<std::string> rowHeaders;
		std::string columnName;
		std::string result;
		//sqlite3_stmt* statement;
		char** pargs = &tableName;
		char* nextArg = NULL;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result += "UPDATE " + std::string(tableName) + " SET ";

		for (std::map<std::string, std::string>::iterator it = columnValues.begin();
			it != columnValues.end();
			it++)
		{
			std::pair<std::string, std::string> par = *it;
			Log::debug(par.first.c_str());
			result += par.first + " = " + par.second;

			std::map<std::string, std::string>::iterator temp = it;
			temp++;
			if (temp != columnValues.end())
				result += ", ";
		}

		result += " WHERE " + std::string(whereExpr);

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			if (errMsg != NULL)
				Log::error(errMsg);
			else
				Log::error("Error desconocido sin mensaje");
			sqlite3_free(errMsg);
			//sqlite3_close(db);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rowChanged : rc;
	}

	long Database::DeleteRow(char* tableName, std::string whereExpr)
	{
		std::string result;
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		result
			+= "DELETE FROM " + std::string(tableName);

		if (whereExpr != "")
		{
			result += " WHERE " + whereExpr;
		}

		Log::debug(result.c_str());

		rc = sqlite3_exec(db, result.c_str(), 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_free(errMsg);
			return -1;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rowChanged > 0 ? rowChanged : rc;
	}

	int Database::ExecuteSQL(const char* result)
	{
		char* errMsg = NULL;
		long rowChanged = -1;
		int rc;

		Log::info(__FUNCTION__);

		Log::debug(result);

		rc = sqlite3_exec(db, result, 0, 0, &errMsg);

		if (rc != SQLITE_OK) {

			Log::error(sqlite3_errmsg(db));
			sqlite3_free(errMsg);
			return SQLITE3_ORM_ERROR;
		}

		rowChanged = sqlite3_changes(db);

		Log::info("Exit");

		return rc;
	}

}