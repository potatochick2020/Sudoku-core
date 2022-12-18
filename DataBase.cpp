#include "DataBase.h"

DatabaseConnection::DatabaseConnection(const char* s)
{
    if (sqlite3_threadsafe() > 0) {
        int retCode = sqlite3_config(SQLITE_CONFIG_SERIALIZED); 
    } else {
        std::cout<<"not safe";
    }

	sqlite3* temp;
	DB = temp; 
	sqlite3_initialize();
	exit = sqlite3_open(s, &DB); 
}

void DatabaseConnection::closeConnection(){
	sqlite3_close(DB);
}

void DatabaseConnection::createTableIfNotExist()
{ 
	char* messageError;

	std::string sql = "CREATE TABLE IF NOT EXISTS Sudoku("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"SudokuValue TEXT NOT NULL UNIQUE );"; //This will be a 81 digit unsigned integer holding a flatten Sudoku
	try
	{ 
		/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		
		if (exit != SQLITE_OK) {
			std::cerr << "Error in createTable function :"<<*messageError << std::endl; 
			sqlite3_free(messageError);
		} 
		
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	} 
}

int DatabaseConnection::insertData(std::string sql)
{ 
	char* messageError;
	std::string temp;
    // std::cout<<sql<<std::endl; 
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL , 0, &messageError);
	
	if (exit != SQLITE_OK) { 
		return 1;
	} else {
		return 0;
	}
 
}

void DatabaseConnection::selectData()
{ 
	char* messageError;

	std::string sql = "SELECT * FROM Sudoku;";
 
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
	exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error in selectData function." << std::endl;
		sqlite3_free(messageError);
	}
	else
		std::cout << "Records selected Successfully!" << std::endl;
 
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
 
}

