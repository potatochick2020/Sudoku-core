#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
 
class DatabaseConnection {
    private:
        sqlite3 *DB;
        int exit;
        const char* fpath;
    public: 
        DatabaseConnection(const char* fpath); // create/open connection
        ~DatabaseConnection(); // close connection
        void createTableIfNotExist();
        void insertData(std::string sql);
        void selectData();
        void callback(void* NotUsed, int argc, char** argv, char** azColName);
};



 