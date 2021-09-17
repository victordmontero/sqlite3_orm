#ifndef TABLERESULT_H_
#define TABLERESULT_H_

#include <string>
#include <vector>
#include <map>

namespace sqlite3_orm
{
	class TableResult
	{
		std::string tableName;
		std::map<std::string, std::vector<std::string> > resultSet;
		std::vector<std::string> resultHeaders;
		long rowCount;
		int rowIndex;
		int sqliteResult;

	public:
		TableResult(std::string tableName)
			: tableName(tableName), rowIndex(0), rowCount(0)
		{
			
		};

		std::string operator[](const std::string);

		bool addRow(
			std::vector<std::string> resultHeaders,
			std::vector<std::string> resultRow);
		void firstRow();
		void lastRow();
		bool nextRow();
		bool previousRow();
		long getRowCount();
		const std::vector<std::string>& getResultHeaders();

		int getSqliteResult() const { return sqliteResult; }
		void setSqliteResult(int sqliteResult) { this->sqliteResult = sqliteResult; }
	};
}

#endif
