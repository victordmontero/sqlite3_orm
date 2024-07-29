#include <iostream>
#include <assert.h>
#include <vector>
#include <map>
#include "log.hpp"
#include "sqlite3_orm.hpp"
#include "string.hpp"

void debug(const char* msg)
{
	std::cout << msg << "\n";
}

int main(int args, char* argv[])
{
	long rowsChanged = -1L;
	sqlite3_orm::Log::setLogInfoCallback(debug);
	sqlite3_orm::Log::setLogDebugCallback(debug);
	sqlite3_orm::Log::setLogErrorCallback(debug);

	//Database creation
	sqlite3_orm::Database database("contacts.sqlite3");
	database.Open();

	sqlite3_orm::PrimaryKeyConstraint primaryKeyColumnConstraint("", true, true);
	sqlite3_orm::UniqueConstraint contactNameColumnConstraint;
	sqlite3_orm::ColumnConstraint contactPhoneColumnConstraint;

	//Table creation

	std::string createTableStmtSqlStr = "CREATE TABLE CONTACTS(";

	createTableStmtSqlStr += "Id INTEGER ";
	createTableStmtSqlStr += primaryKeyColumnConstraint.parse();
	createTableStmtSqlStr += ",";
	createTableStmtSqlStr += "ContactName VARCHAR(20) ";
	createTableStmtSqlStr += contactNameColumnConstraint.parse();
	createTableStmtSqlStr += ",";
	createTableStmtSqlStr += "ContactPhone VARCHAR(14) ";
	createTableStmtSqlStr += contactPhoneColumnConstraint.parse();

	createTableStmtSqlStr += ")";

	database.ExecuteSQL(createTableStmtSqlStr.c_str());

	//Inserting a row
	std::map<std::string, std::string> columnNames;
	columnNames["ContactName"] = sqlite3_orm::string("Diana").ToSqlString();
	columnNames["ContactPhone"] = sqlite3_orm::string("020 7123 4567").ToSqlString();

	//Beginning a transaction to ensure atomic transactions
	database.BeginTran();
	rowsChanged = database.InsertIntoTable("CONTACTS", columnNames);
	database.Commit();
	printf("rowsChanged = %ld\n", rowsChanged);

	//Selecting from CONTACTS table
	sqlite3_orm::TableResult tableResult = database.SelectTableAll("CONTACTS");
	tableResult.firstRow();
	printf("Rows=[%d]\n", tableResult.getRowCount());

	for (int i = 0; i < tableResult.getRowCount(); i++)
	{
		printf("%s\t%s\t%s\n", tableResult["Id"].c_str(),
			tableResult["ContactName"].c_str(), tableResult["ContactPhone"].c_str());
		tableResult.nextRow();
	}

	tableResult.lastRow();

	//Updating a row
	database.BeginTran();

	std::map<std::string, std::string> updateColumnNames;
	//updateColumnNames["Id"] = "1";
	updateColumnNames["ContactName"] = sqlite3_orm::string("Meghan").ToSqlString();
	updateColumnNames["ContactPhone"] = sqlite3_orm::string("020 3217 7654").ToSqlString();

	rowsChanged = database.UpdateTable(
		"CONTACTS",
		(char*)(std::string("Id = ") + tableResult["Id"]).c_str(),
		updateColumnNames);

	printf("rowsChanged = %ld\n", rowsChanged);

	database.Commit();

	//Selecting again
	tableResult = database.SelectTableAll("CONTACTS");
	tableResult.firstRow();
	printf("Rows=[%d]\n", tableResult.getRowCount());

	for (int i = 0; i < tableResult.getRowCount(); i++)
	{
		printf("%s\t%s\t%s\n", tableResult["Id"].c_str(),
			tableResult["ContactName"].c_str(), tableResult["ContactPhone"].c_str());
		tableResult.nextRow();
	}

	tableResult.lastRow();

	//Inserting another row
	columnNames["ContactName"] = sqlite3_orm::string("Diana").ToSqlString();
	columnNames["ContactPhone"] = sqlite3_orm::string("020 7123 4567").ToSqlString();

	//Beginning a transaction to ensure atomic transactions
	database.BeginTran();
	rowsChanged = database.InsertIntoTable("CONTACTS", columnNames);
	database.Commit();
	printf("rowsChanged = %ld\n", rowsChanged);

	//Deleting all rows
	database.BeginTran();
	rowsChanged = database.DeleteRow("CONTACTS");
	printf("rowsChanged = %ld\n", rowsChanged);
	database.Commit();

	database.Close();

}