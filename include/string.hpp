#ifndef STRING_HPP_
#define STRING_HPP_

#include <string>

namespace sqlite3_orm {
	class string: public std::string
	{
	public:
		string(const char* const text);
		~string();

		string& ToSqlString();

	private:
	};
}

#endif