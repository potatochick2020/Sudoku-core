#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
 
int createDB(const char* s);
int createTable(const char* s);
int deleteData(const char* s);
int insertData(const char* s, std::string query);
int updateData(const char* s);
int selectData(const char* s);
int callback(void* NotUsed, int argc, char** argv, char** azColName);

 
int createDB(const char* s);

int createTable(const char* s);

int insertData(const char* s , std::string query);

int selectData(const char* s);
 
int callback(void* NotUsed, int argc, char** argv, char** azColName);