#include<tableresult.hpp>

namespace sqlite3_orm
{
	std::string TableResult::operator[](const std::string name)
	{
		return resultSet[name][rowIndex];
	}

	bool TableResult::addRow(
		std::vector<std::string> resultHeaders,
		std::vector<std::string> resultRow)
	{
		this->resultHeaders = resultHeaders;
		if (this->resultHeaders.size() == resultHeaders.size())
		{
			for (size_t i = 0; i < resultHeaders.size(); i++)
			{
				resultSet[resultHeaders[i]].push_back(resultRow[i]);
			}
			rowCount++;
			return true;
		}
		return false;
	}

	void TableResult::firstRow()
	{
		rowIndex = 0;
	}

	bool TableResult::nextRow()
	{
		return rowIndex++ < rowCount - 1;
	}

	bool TableResult::previousRow()
	{
		bool result = rowIndex-- >= 0;
		if (rowIndex < 0)
			rowIndex = 0;
		return result;
	}

	void TableResult::lastRow()
	{
		rowIndex = rowCount - 1;
	}

	long TableResult::getRowCount()
	{
		return rowCount;
	}

	const std::vector<std::string>& TableResult::getResultHeaders()
	{
		return resultHeaders;
	}
}