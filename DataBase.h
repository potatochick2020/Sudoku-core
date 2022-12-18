#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include <atomic>

#pragma once
class DatabaseConnection { 
    private:
        sqlite3 *DB;
        int exit;
        const char* fpath; 
    public: 
        DatabaseConnection(const char* fpath); // create/open connection
        // ~DatabaseConnection(); // close connection
        void createTableIfNotExist();
        int insertData(std::string sql); // return 0 if success
        void selectData();
        void callback(void* NotUsed, int argc, char** argv, char** azColName);
        void closeConnection(); 
};



 