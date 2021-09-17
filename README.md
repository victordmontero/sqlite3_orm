# Sqlite3 ORM

**Sqlite3 ORM** is an [Object Relational Mapper] implemented in C++ standard 1993.

## To use:

```cpp
    sqlite3_orm::Database database("C:/contacts.sqlite3");
	database.Open();

	sqlite3_orm::TableResult tableResult = database.SelectTableAll("CONTACTS");

	tableResult.firstRow();

	for(int i = 0;i < tableResult.getRowCount(); i++)
	{
		printf("%s:%s\n",
		    tableResult["ContactName"].c_str(),
			tableResult["ContactTelephoneNumber"].c_str());
		tableResult.nextRow();
	}
	
	database.Close();
```


[Object Relational Mapper]:<https://en.wikipedia.org/wiki/Object%E2%80%93relational_mapping>