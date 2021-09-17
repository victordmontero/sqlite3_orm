#include<string.hpp>

namespace sqlite3_orm {

	string::string(const char* const text) : std::string(text)
	{

	}

	string::~string()
	{
		std::string::~basic_string();
	}

	string& string::ToSqlString()
	{
		this->insert(0, "'");
		this->append("'");
		return *this;
	}
}