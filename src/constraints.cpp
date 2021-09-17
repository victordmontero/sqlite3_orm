#include<constraints.hpp>
#include<log.hpp>

namespace sqlite3_orm
{
	/*Begin ColumnConstraint*/
	ColumnConstraint::ColumnConstraint(std::string constraintName)
		: constraintName(constraintName)
	{
		Log::info("ColumnConstraint");
		
	}

	const std::string ColumnConstraint::getConstraintName() const
	{
		return constraintName;
	}

	std::string ColumnConstraint::parse()
	{
		Log::info("ColumnConstraint::parse()");
		if (!constraintName.empty())
		{
			std::string result;
			result += "CONSTRAINT "
				+ getConstraintName()
				+ " ";
			Log::info(result.c_str());
			return result;
		}
		return "";
	}
	/*End ColumnConstraint*/

	/*Begin PrimaryKeyConstraint*/
	bool PrimaryKeyConstraint::getIsAscending() const
	{
		return isAscending;
	}

	bool PrimaryKeyConstraint::getIsAutoIncrement() const
	{
		return isAutoIncrement;
	}

	std::string PrimaryKeyConstraint::parse()
	{
		std::string result;

		result += ColumnConstraint::parse() + "PRIMARY KEY "
			+ (getIsAscending() ? "ASC" : "DESC")
			+ (getIsAutoIncrement() ? " AUTOINCREMENT" : "");

		return result;
	}
	/*End PrimaryKeyConstraint*/


	/*Begin UniqueConstraint*/
	std::string UniqueConstraint::parse()
	{
		std::string result;

		result += ColumnConstraint::parse()
			+ "UNIQUE";

		return result;
	}
	/*End UniqueConstraint*/

	/*Begin CollateConstraint*/
	std::string CollateConstraint::getCollateName() const
	{
		return collateName;
	}

	std::string CollateConstraint::parse()
	{
		std::string result;

		result += ColumnConstraint::parse()
			+ "COLLATE " + getCollateName();

		return result;
	}
	/*End CollateConstraint*/

	/*Begin CheckConstraint*/
	const std::string CheckConstraint::getExpression() const
	{
		return expression;
	}

	std::string CheckConstraint::parse()
	{
		std::string result;

		result += ColumnConstraint::parse()
			+ "CHECK (" + getExpression() + ")";

		return result;
	}
	/*End CheckConstraint*/

	/*Begin DefaultConstraint*/
	const std::string DefaultConstraint::getLiteralValue() const
	{
		return literalValue;
	}

	long DefaultConstraint::getSignedValue()
	{
		return signedValue;
	}

	bool DefaultConstraint::getIsLiteralValue()
	{
		return isLiteralValue;
	}

	bool DefaultConstraint::getIsSignedValue()
	{
		return isSignedValue;
	}

	std::string DefaultConstraint::parse()
	{
		std::string result;

		result += ColumnConstraint::parse()
			+ "DEFAULT ";

		if (getIsSignedValue()) {
			result += getSignedValue();
		}
		else if (getIsLiteralValue())
			result += getLiteralValue();
		else
			result += "(" + CheckConstraint::getExpression() + ")";

		return result;
	}
	/*End DefaultConstraint*/


}