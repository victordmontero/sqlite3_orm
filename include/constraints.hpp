#ifndef CONSTRAINTS_HPP_
#define CONSTRAINTS_HPP_

#include <string>
#include<enums.hpp>
#include<parse.hpp>

namespace sqlite3_orm
{
	class ColumnConstraint : public Parseable
	{
		std::string constraintName;
	public:
		explicit ColumnConstraint(std::string constraintName = "");
		virtual const std::string getConstraintName() const;
		virtual std::string parse();
	};

	class PrimaryKeyConstraint : public ColumnConstraint
	{
		bool isAscending;
		bool isAutoIncrement;
	public:
		PrimaryKeyConstraint(
			std::string constraintName = "",
			bool isAscending = true,
			bool isAutoIncrement = false)
			: ColumnConstraint(constraintName),
			isAscending(isAscending),
			isAutoIncrement(isAutoIncrement) {}

		virtual bool getIsAscending() const;
		virtual bool getIsAutoIncrement() const;

		virtual std::string parse();
	};

	class UniqueConstraint : public ColumnConstraint
	{
	public:
		explicit UniqueConstraint(std::string constraintName = "")
			: ColumnConstraint(constraintName) {}

		virtual std::string parse();
	};

	
	class CollateConstraint : public ColumnConstraint
	{
		std::string collateName;
	public:
		CollateConstraint(std::string collateName,
			std::string constraintName = "")
			: ColumnConstraint(constraintName),
			collateName(collateName) {}

		virtual std::string getCollateName() const;
		virtual std::string parse();
	};

	class CheckConstraint : public ColumnConstraint
	{
		std::string expression;
	public:
		explicit CheckConstraint(std::string expression, std::string constraintName = "")
			: ColumnConstraint(constraintName), expression(expression) {}
		virtual const std::string getExpression() const;
		virtual std::string parse();
	};

	class DefaultConstraint : public CheckConstraint
	{
		std::string literalValue;
		long signedValue;
		bool isLiteralValue;
		bool isSignedValue;
	public:
		explicit DefaultConstraint(std::string expression,
			std::string constraintName = "",
			bool isLiteralValue = false,
			bool isSignedValue = false,
			std::string literalValue = "",
			long signedValue = 0L)
			: CheckConstraint(expression, constraintName),
			literalValue(literalValue),
			signedValue(signedValue),
			isLiteralValue(isLiteralValue),
			isSignedValue(isSignedValue) {}

		const std::string getLiteralValue() const;
		long getSignedValue();
		bool getIsLiteralValue();
		bool getIsSignedValue();

		virtual std::string parse();

	};
}

#endif