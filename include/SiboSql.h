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
    /**
     * constructor
     * @author Meraj
     * @since 0.1.0
     */
    SiboSql();

    /**
    * constructor
    * @param dbName char -> set database name
    * @author Meraj
    * @since 0.1.0
    */
    SiboSql(char *dbName);

    /**
    * constructor
    * @param dbName std::string -> set database name
    * @author Meraj
    * @since 0.1.0
    */
    SiboSql(std::string dbName);

    SiboSql setVersion(int version);

    /**
    * constructor
    * @param tableName std::string -> set table name
    */
    SiboSql table(std::string tableName);

    /**
     * create id column
     * @author Meraj
     * @since 0.1.0
     */
    SiboSql id();

    /**
     * make column
     * @param columnName std::string
     * @param dataType std::string
     * @author Meraj
     * @since 0.1.0
     */
    SiboSql column(std::string columnName, std::string dataType);

    /**
     * create database tables
     * @author Meraj
     * @since 0.1.0
     */
    void init();


    void query(std::string query);

    /**
     * execute query
     * @return sqlite3_stmt*
     * @author Meraj
     * @since 0.1.1
     */
    sqlite3_stmt *execute();

    /**
     * execute query and callback function
     * @param query std::string
     * @param callback int (*callback)(void *, int, char **, char **)
     * @author Meraj
     * @since 0.1.0
     */
    void query(std::string query, int (*callback)(void *, int, char **, char **));

    // NOT READY
    static std::vector<std::map<std::string, char *>> stmtToArray(sqlite3_stmt *Stmt);
};


#endif //SIBOSQL_SIBOSQL_H
