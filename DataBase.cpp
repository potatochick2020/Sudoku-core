#include "DataBase.h"

DatabaseConnection::DatabaseConnection(const char* s)
{
    if (sqlite3_threadsafe() > 0) {
        int retCode = sqlite3_config(SQLITE_CONFIG_SERIALIZED); 
    } else {
        std::cout<<"not safe";
    }

	// sqlite3* DB;
	// sqlite3_initialize();
	// int exit = 0;
	// exit = sqlite3_open(s, &DB);

	// sqlite3_close(DB);
 
	sqlite3_initialize();
	exit = sqlite3_open(s, *DB);

	// sqlite3_close(DB);

	return 0;
}

DatabaseConnection::~DatabaseConnection(){
	sqlite3_close(*DB);
}

void DatabaseConnection::createTableIfNotExist()
{ 
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS Sudoku("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"SudokuValue BLOB NOT NULL UNIQUE );"; //This will be a 81 digit unsigned integer holding a flatten Sudoku
	try
	{ 
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createTable function." << std::endl;
			sqlite3_free(messageError);
		}
		else
			std::cout << "Table created Successfully" << std::endl; 
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	} 
}

void DatabaseConnection::insertData(std::string sql)
{ 
	char* messageError;
		 
    std::cout<<query<<std::endl; 
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error in insertData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records inserted Successfully!" << std::endl;
 
}

void DatabaseConnection::selectData()
{ 
	char* messageError;

	std::string sql = "SELECT * FROM Sudoku;";
 
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;

	return 0;
}

// retrieve contents of database used by selectData()
/* argc: holds the number of results, argv: holds each value in array, azColName: holds each column returned in array, */
void DatabaseConnection::callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	for (int i = 0; i < argc; i++) {
		// column name and value
        std::cout.setf(std::ios::fixed);
		std::cout << azColName[i] << ": " << argv[i] << std::endl;
	}

	std::cout << std::endl;

	return 0;
}

