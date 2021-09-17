#include <iostream>
#include <assert.h>
#include <sqlite3_orm.hpp>
#include <log.hpp>
#include <vector>
#include <map>

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

	sqlite3_orm::Database database("softpay.sqlite3");
	database.Open();

	sqlite3_orm::TableResult tableResult = database.SelectTableAll("SP_TERMINALS");

	tableResult.firstRow();
	printf("Rows=[%d]\n", tableResult.getRowCount());

	for (int i = 0; i < tableResult.getRowCount(); i++)
	{
		printf("%s:%s\n", tableResult["TerminalId"].c_str(),
			tableResult["TerminalModelName"].c_str());
		tableResult.nextRow();
	}

	tableResult.lastRow();

	printf("TerminalId = %s\n", tableResult["TerminalId"].c_str());

	database.BeginTran();

	std::map<std::string, std::string> updateColumnNames;
	updateColumnNames["Mobile"] = "1";
	updateColumnNames["Color"] = "1";
	updateColumnNames["BuiltInPrinter"] = "0";

	rowsChanged = database.UpdateTable(
		"SP_TERMINALS",
		(char*)(std::string("TerminalId = ") + tableResult["TerminalId"]).c_str(),
		updateColumnNames);

	printf("rowsChanged = %ld\n", rowsChanged);


	tableResult.previousRow();
	std::map<std::string, std::string> updateColumnNames2;
	updateColumnNames2["Mobile"] = "1";
	updateColumnNames2["Color"] = "1";
	updateColumnNames2["BuiltInPrinter"] = "0";

	rowsChanged = database.UpdateTable(
		"SP_TERMINALS",
		(char*)(std::string("TerminalId = ") + tableResult["TerminalId"]).c_str(),
		updateColumnNames2);

	printf("rowsChanged = %ld\n", rowsChanged);

	database.Commit();
	database.BeginTran();

	rowsChanged = database.DeleteRow("SP_TERMINALS");
	printf("rowsChanged = %ld\n", rowsChanged);

	database.Commit();
	database.Close();
}