#ifndef ENUMS_HPP_
#define ENUMS_HPP_

namespace sqlite3_orm_ColumnType
{
	enum ColumnType
	{
		INTEGER,
		REAL,
		TEXT,
		BLOB,
		NULL_TYPE
	};
}

namespace sqlite3_orm_TableConstraintType
{
	enum TableConstraintType
	{
		PRIMARY_KEY,
		FOREIGN_KEY,
		UNIQUE,
		CHECK
	};
}

#endif