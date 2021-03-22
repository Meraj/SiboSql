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
    SiboSql bind(int index,int value);
    SiboSql bind(int index,char value);
    SiboSql bind(int index,std::string value);
    SiboSql bind(int index,double value);
    SiboSql query(std::string query);
    sqlite3_stmt* execute();
    void query(std::string query,int (*callback)(void *, int, char **, char **));
};


#endif //SIBOSQL_SIBOSQL_H
