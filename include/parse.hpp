#ifndef PARSE_HPP_
#define PARSE_HPP_

#include <string>

namespace sqlite3_orm
{
	class Parseable
	{
	public:
		virtual std::string parse() = 0;
	};
}

#endif