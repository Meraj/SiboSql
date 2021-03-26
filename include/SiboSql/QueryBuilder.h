//
// Created by Meraj on 3/24/2021.
//

#ifndef SIBOSQL_QUERYBUILDER_H
#define SIBOSQL_QUERYBUILDER_H

#include <iostream>
#include <vector>
#include <sqlite3.h>
class QueryBuilder {
private:
    std::string query;
    sqlite3 *db;
    sqlite3_stmt *stmt;
    std::string Table_str;
    bool doBind = true;
    std::vector<std::string> bindParamsVector;
    int INSERT = 0;
    std::string select_statement;
    std::string where_statement;
    std::string orderBy_statement
public:
    QueryBuilder(sqlite3 *db);
    std::string buildQuery(int type);
    std::string buildQuery(int type,std::vector<std::string> columns,std::vector<std::string> values);
    QueryBuilder table(std::string table);
    // select
    QueryBuilder select(std::string column);
    QueryBuilder addSelect(std::string column);
    QueryBuilder select(const std::vector<std::string>& columns);
    QueryBuilder addSelect(std::vector<std::string> columns);
    QueryBuilder selectRaw(std::string selectRaw);
    // Where
    QueryBuilder where(std::string column,std::string value);
    QueryBuilder whereRaw(std::string);
    QueryBuilder orWhere(std::string column,std::string value);
    // order by
    QueryBuilder orderBy(std::string column,std::string type = "asc");
    // update
    sqlite3_stmt *update(std::vector<std::string> columns,std::vector<std::string> values);
    //insert
    sqlite3_stmt *insert(std::vector<std::string> columns,std::vector<std::string> values);
    // count
    int count();
    // exists
    bool exists();
    bool doesNotExist();
    // BIND
    void bind(int index, int value);

    void bind(int index, std::string value);

    void bind(int index, double value);

    // execute
    sqlite3_stmt *execute(std::string query);
};


#endif //SIBOSQL_QUERYBUILDER_H
