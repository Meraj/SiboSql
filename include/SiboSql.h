//
// Created by Meraj on 3/22/2021.
//

#ifndef SIBOSQL_SIBOSQL_H
#define SIBOSQL_SIBOSQL_H

#include <iostream>
#include <sqlite3.h>
#include <bits/stdc++.h>
#include <vector>
class SiboSql {
private:
    sqlite3 *db;
    int rc;
    sqlite3_stmt *stmt;
    std::string tableQuery;
    std::vector<std::string> queries;
public:
    SiboSql();
    SiboSql(char* dbName);
    SiboSql(std::string dbName);
    SiboSql setVersion(int version);
    SiboSql table(std::string tableName);
    SiboSql id();
    SiboSql column(std::string columnName,std::string dataType);
    void init();
    sqlite3_stmt* query(std::string query);
    void query(std::string query,std::function<int (void*,int,char**,char**)> callback);
};


#endif //SIBOSQL_SIBOSQL_H
