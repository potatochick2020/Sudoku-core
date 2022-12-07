#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
 
class DatabaseConnection {
    private:
        sqlite3 *DB;
        int exit;
        const char* fpath;
    public: 
        int createOrOpenDB(const char* fpath);
        int closeDB();
        int createTableIfNotExist();
        int insertData(std::string query);
        int selectData();
        int callback(void* NotUsed, int argc, char** argv, char** azColName);

}



 