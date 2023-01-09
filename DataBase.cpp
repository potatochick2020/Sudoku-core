#include "DataBase.hpp"

DatabaseConnection::DatabaseConnection(const char* path)
{

	std::ifstream file; 
    file.open(path);
	if (file){
		fpath = path;  
		if (sqlite3_threadsafe() > 0) {
			int retCode = sqlite3_config(SQLITE_CONFIG_SERIALIZED); 
		} else {
			std::cout<<"not safe";
		}
	
		sqlite3_initialize();
		exit = sqlite3_open(fpath, &DB); 
	} else {
		exit = SQLITE_NOTFOUND; 
	}
	
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

int DatabaseConnection::insertData(const std::string& sql)
{ 
	char* messageError; 
    // std::cout<<sql<<std::endl; 
	/* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
	exit = sqlite3_exec(DB, sql.c_str(), NULL , 0, &messageError);
	
	if (exit != SQLITE_OK) { 
		return 1;
	} else {
		return 0;
	}
 
}
 