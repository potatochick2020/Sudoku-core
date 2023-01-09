#include <sqlite3.h>  
#include <fstream>
#include <iostream>

#pragma once
class DatabaseConnection { 
    private:
        sqlite3 *DB;
        int exit;
        const char* fpath; 
    public: 
        DatabaseConnection(const char* path);
        void createTableIfNotExist();
        int insertData(const std::string& sql);
        void closeConnection(); 
        int getDBstatus(){
            return exit;
        }
        
};



 