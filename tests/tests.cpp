#include <gtest/gtest.h>
#include <iostream>
#include <log.hpp>
#include <map>
#include <sqlite3_orm.hpp>
#include <string.hpp>
#include <vector>

void debug(const char *msg)
{
    std::cout << msg << "\n";
}

class utSqlite3Orm : public testing::Test
{
  public:
    utSqlite3Orm() : testing::Test(), database(NULL)
    {
    }

    void SetUp() override
    {
        testing::Test::SetUp();

#ifdef DEBUG
        sqlite3_orm::Log::setLogInfoCallback(debug);
        sqlite3_orm::Log::setLogDebugCallback(debug);
        sqlite3_orm::Log::setLogErrorCallback(debug);
#endif

        database = new sqlite3_orm::Database(":memory:");
        database->Open();
    }

    void TearDown() override
    {
        database->Close();
        delete database;
        database = NULL;
    }

    sqlite3_orm::Database *database;
};

TEST(sqlite3_orm_uttests, open_database_test)
{
    int rc = -1;
    sqlite3_orm::Database open_database_test("/tmp/open_test_db.sqlite3");
    rc = open_database_test.Open();
    open_database_test.Close();
    EXPECT_EQ(rc, 0);
}

TEST_F(utSqlite3Orm, execute_sql_test)
{
    int rc = database->ExecuteSQL("PRAGMA encoding");
    EXPECT_EQ(rc, SQLITE3_ORM_OK);
}

TEST_F(utSqlite3Orm, insert_test)
{
    int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE(id INTEGER, NM CHAR(2))");

    EXPECT_EQ(rc, SQLITE3_ORM_OK);

    std::map<std::string, std::string> columnValues;
    columnValues["id"] = "1";
    columnValues["NM"] = sqlite3_orm::string("XX").ToSqlString();
    rc = database->InsertIntoTable("TEST_TABLE", columnValues);

    EXPECT_EQ(rc, 1);
}

TEST_F(utSqlite3Orm, update_test)
{
    int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE2(id INTEGER, NM CHAR(2))");

    EXPECT_EQ(rc, SQLITE3_ORM_OK);

    std::map<std::string, std::string> columnValues;
    columnValues["id"] = "1";
    columnValues["NM"] = sqlite3_orm::string("XX").ToSqlString();
    rc = database->InsertIntoTable("TEST_TABLE2", columnValues);
    EXPECT_EQ(rc, 1);
    columnValues.clear();
    columnValues["NM"] = sqlite3_orm::string("ZZ").ToSqlString();
    rc = database->UpdateTable("TEST_TABLE2", "id=1", columnValues);
    EXPECT_EQ(rc, 1);
}

TEST_F(utSqlite3Orm, delete_test)
{
    int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE3(id INTEGER, NM CHAR(2))");

    EXPECT_EQ(rc, SQLITE3_ORM_OK);

    std::map<std::string, std::string> columnValues;
    columnValues["id"] = "1";
    columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
    rc = database->InsertIntoTable("TEST_TABLE3", columnValues);
    EXPECT_EQ(rc, 1);
    rc = database->DeleteRow("TEST_TABLE3", "id=1");
    EXPECT_EQ(rc, 1);
}

TEST_F(utSqlite3Orm, string_sql_test)
{
    sqlite3_orm::string test_string = "TEST_VALUE";
    EXPECT_STREQ(test_string.ToSqlString().c_str(), "'TEST_VALUE'");
}

TEST_F(utSqlite3Orm, commit_tran_test)
{
    int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE4(id INTEGER, NM CHAR(2))");

    EXPECT_EQ(rc, SQLITE3_ORM_OK);

    std::map<std::string, std::string> columnValues;
    columnValues["id"] = "1";
    columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
    rc = database->InsertIntoTable("TEST_TABLE4", columnValues);
    EXPECT_EQ(rc, 1);
    database->BeginTran();
    rc = database->DeleteRow("TEST_TABLE4", "id=1");
    EXPECT_EQ(rc, 1);
    database->Commit();
    rc = database->DeleteRow("TEST_TABLE4", "id=1");
    EXPECT_EQ(rc, 0);
}

TEST_F(utSqlite3Orm, rollback_tran_test)
{
    int rc = database->ExecuteSQL("CREATE TABLE TEST_TABLE5(id INTEGER, NM CHAR(2))");

    EXPECT_EQ(rc, SQLITE3_ORM_OK);

    std::map<std::string, std::string> columnValues;
    columnValues["id"] = "1";
    columnValues["NM"] = sqlite3_orm::string("XZ").ToSqlString();
    rc = database->InsertIntoTable("TEST_TABLE5", columnValues);
    EXPECT_EQ(rc, 1);
    database->BeginTran();
    rc = database->DeleteRow("TEST_TABLE5", "id=1");
    EXPECT_EQ(rc, 1);
    database->RollBack();
    rc = database->DeleteRow("TEST_TABLE5", "id=1");
    EXPECT_EQ(rc, 1);
}
