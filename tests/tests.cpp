#include <iostream>
#include <vector>
#include <map>
#include <check.h>
#include <sqlite3_orm.hpp>
#include <log.hpp>
#include <string.hpp>

sqlite3_orm::Database* database = NULL;

void debug(const char* msg)
{
	std::cout << msg << "\n";
}

void setup()
{
#ifdef DEBUG
	sqlite3_orm::Log::setLogInfoCallback(debug);
	sqlite3_orm::Log::setLogDebugCallback(debug);
	sqlite3_orm::Log::setLogErrorCallback(debug);
#endif

	database = new sqlite3_orm::Database(":memory:");
	database->Open();
}

void tearDown()
{
	database->Close();
	delete database;
	database = NULL;
}

START_TEST(open_database_test)
{
	int rc = -1;
	sqlite3_orm::Database open_database_test("open_test_db.sqlite3");
	rc = open_database_test.Open();
	open_database_test.Close();
	ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(execute_sql_test)
{
	int rc = database->ExecuteSQL("PRAGMA encoding");
	ck_assert_int_eq(rc, SQLITE3_ORM_OK);
}
END_TEST

START_TEST(insert_test)
{
	int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE(id INTEGER, NM CHAR(2))");

	ck_assert_int_eq(rc, SQLITE3_ORM_OK);

	std::map<std::string, std::string> columnValues;
	columnValues["id"] = "1";
	columnValues["NM"] = sqlite3_orm::string("XX").ToSqlString();
	rc = database->InsertIntoTable("TEST_TABLE", columnValues);

	ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(update_test)
{
	int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE2(id INTEGER, NM CHAR(2))");

	ck_assert_int_eq(rc, SQLITE3_ORM_OK);

	std::map<std::string, std::string> columnValues;
	columnValues["id"] = "1";
	columnValues["NM"] = sqlite3_orm::string("XX").ToSqlString();
	rc = database->InsertIntoTable("TEST_TABLE2", columnValues);
	ck_assert_int_eq(rc, 1);
	columnValues.clear();
	columnValues["NM"] = sqlite3_orm::string("ZZ").ToSqlString();
	rc = database->UpdateTable("TEST_TABLE2", "id=1", columnValues);
	ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(delete_test)
{
	int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE3(id INTEGER, NM CHAR(2))");

	ck_assert_int_eq(rc, SQLITE3_ORM_OK);

	std::map<std::string, std::string> columnValues;
	columnValues["id"] = "1";
	columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
	rc = database->InsertIntoTable("TEST_TABLE3", columnValues);
	ck_assert_int_eq(rc, 1);
	rc = database->DeleteRow("TEST_TABLE3", "id=1");
	ck_assert_int_eq(rc, 1);
}
END_TEST

START_TEST(string_sql_test)
{
	sqlite3_orm::string test_string = "TEST_VALUE";
	ck_assert_str_eq(test_string.ToSqlString().c_str(), "'TEST_VALUE'");
}
END_TEST

START_TEST(commit_tran_test)
{
	int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE4(id INTEGER, NM CHAR(2))");

	ck_assert_int_eq(rc, SQLITE3_ORM_OK);

	std::map<std::string, std::string> columnValues;
	columnValues["id"] = "1";
	columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
	rc = database->InsertIntoTable("TEST_TABLE4", columnValues);
	ck_assert_int_eq(rc, 1);
	database->BeginTran();
	rc = database->DeleteRow("TEST_TABLE4", "id=1");
	ck_assert_int_eq(rc, 1);
	database->Commit();
	rc = database->DeleteRow("TEST_TABLE4", "id=1");
	ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(rollback_tran_test)
{
	int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE5(id INTEGER, NM CHAR(2))");

	ck_assert_int_eq(rc, SQLITE3_ORM_OK);

	std::map<std::string, std::string> columnValues;
	columnValues["id"] = "1";
	columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
	rc = database->InsertIntoTable("TEST_TABLE5", columnValues);
	ck_assert_int_eq(rc, 1);
	database->BeginTran();
	rc = database->DeleteRow("TEST_TABLE5", "id=1");
	ck_assert_int_eq(rc, 1);
	database->RollBack();
	rc = database->DeleteRow("TEST_TABLE5", "id=1");
	ck_assert_int_eq(rc, 1);
}
END_TEST

Suite* suite(void)
{
	Suite* s = suite_create("sqlite3_orm");
	TCase* tc_core = tcase_create("core");
	tcase_add_checked_fixture(tc_core, setup, tearDown);
	tcase_add_test(tc_core, string_sql_test);
	tcase_add_test(tc_core, open_database_test);
	tcase_add_test(tc_core, execute_sql_test);
	tcase_add_test(tc_core, insert_test);
	tcase_add_test(tc_core, update_test);
	tcase_add_test(tc_core, delete_test);
	tcase_add_test(tc_core, commit_tran_test);
	tcase_add_test(tc_core, rollback_tran_test);
	suite_add_tcase(s, tc_core);
	return s;
}

int main(int args, char* argv[])
{
	/********************************************************************/

	int numberFailed;
	Suite* s = suite();
	SRunner* sr = srunner_create(s);
	srunner_set_fork_status(sr, CK_NOFORK);
	srunner_run_all(sr, CK_NORMAL);
	numberFailed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return numberFailed == 0 ? 0 : 1;

	/********************************************************************/

#if 0
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

	/*std::map<std::string, std::string> columnNames;
	columnNames["TerminalModelName"] = "'E355X'";
	columnNames["BuiltInPrinter"] = "0";
	columnNames["Mobile"] = "0";
	columnNames["Color"] = "0";

	rowsChanged = database.InsertIntoTable("SP_TERMINALS", columnNames);
	printf("rowsChanged = %ld\n", rowsChanged);*/

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

	sqlite3_orm::ColumnConstraint columnConstraint("columnName");
	std::cout << columnConstraint.parse() << "\n";

	assert(columnConstraint.getConstraintName() == "columnName");
	assert(columnConstraint.parse() == "CONSTRAINT columnName ");

	sqlite3_orm::PrimaryKeyConstraint primaryKeyColumn("columnName");
	std::cout << primaryKeyColumn.parse() << "\n";

	assert(primaryKeyColumn.getConstraintName() == "columnName");
	assert(primaryKeyColumn.parse() == "CONSTRAINT columnName PRIMARY KEY ASC");

	sqlite3_orm::PrimaryKeyConstraint primaryKey2Column("", false, true);
	std::cout << primaryKey2Column.parse() << "\n";

	assert(primaryKey2Column.parse() == "PRIMARY KEY DESC AUTOINCREMENT");

	sqlite3_orm::UniqueConstraint uniqueConstraint;
	std::cout << uniqueConstraint.parse() << "\n";

	assert(uniqueConstraint.parse() == "UNIQUE");

	sqlite3_orm::CheckConstraint checkConstraint("Expression");
	std::cout << checkConstraint.parse() << "\n";

	assert(checkConstraint.parse() == "CHECK (Expression)");

	sqlite3_orm::DefaultConstraint defaultConstraint("d");
	std::cout << defaultConstraint.parse() << "\n";

	//assert(checkConstraint.parse() == "DEFAULT (d)");

	sqlite3_orm::CollateConstraint collateConstraint("collateName", "columnName");
	std::cout << collateConstraint.parse() << "\n";

	assert(collateConstraint.getConstraintName() == "columnName");
	assert(collateConstraint.parse() == "CONSTRAINT columnName COLLATE collateName");

	sqlite3_orm::Database database("softpay.sqlite3", 0);
	database.Open();

	/*sqlite3_orm::TableResult tableResult = database.SelectTable(
		"SP_LANGUAGES",
		"LanguageNamePrefix",
		"LanguageNameFontBytes", 0);*/

	sqlite3_orm::TableResult tableResult = database.SelectTableAll("SP_TERMINALS");

	/*std::vector<std::string> rowsResultColumn1;
	rowsResultColumn1.push_back("result11");
	rowsResultColumn1.push_back("result12");

	std::vector<std::string> rowsResultColumn2;
	rowsResultColumn2.push_back("result21");
	rowsResultColumn2.push_back("result22");

	std::vector<std::string> rowsResultColumn3;
	rowsResultColumn3.push_back("result31");
	rowsResultColumn3.push_back("result32");

	std::vector<std::string> rowsNameColumn;
	rowsNameColumn.push_back("column1");
	rowsNameColumn.push_back("column2");

	std::map<std::string, std::vector<std::string>> resultSets;
	resultSets["column1"] = rowsResultColumn1;
	resultSets["column2"] = rowsResultColumn2;*/

	/*sqlite3_orm::TableResult tableResult("SP_LANGUAGES");*/

	/*tableResult.addRow(rowsNameColumn, rowsResultColumn1);
	tableResult.addRow(rowsNameColumn, rowsResultColumn2);
	tableResult.addRow(rowsNameColumn, rowsResultColumn3);*/

	std::cout << std::string(30, '*') << "\n";
	tableResult.firstRow();
	while (tableResult.nextRow())
	{
		for (size_t i = 0; i < tableResult.getResultHeaders().size(); i++)
		{
			std::cout << tableResult.getResultHeaders()[i] << ":"
				<< tableResult[tableResult.getResultHeaders()[i]] << "\n";
		}
		std::cout << std::string(30, '*') << "\n";
	}

	database.Close();
#endif
}