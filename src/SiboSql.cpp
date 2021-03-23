//
// Created by Meraj on 3/22/2021.
//

#include <functional>
#include "../include/SiboSql.h"

SiboSql::SiboSql() {

}

SiboSql::SiboSql(char *dbName) {
    rc = sqlite3_open(dbName, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

SiboSql::SiboSql(std::string dbName) {
    rc = sqlite3_open(dbName.c_str(), &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

SiboSql SiboSql::column(std::string columnName, std::string dataType) {
    this->tableQuery += columnName + " " + dataType + ",";
    return *this;
}

SiboSql SiboSql::table(std::string tableName) {
    if (this->tableQuery.empty()) {
        this->tableQuery += "CREATE TABLE IF NOT EXISTS " + tableName + "(";
    } else {
        this->tableQuery.erase(std::prev(this->tableQuery.end()));
        this->tableQuery += ");";
        this->queries.push_back(this->tableQuery);
        this->tableQuery.clear();
        this->tableQuery += "CREATE TABLE IF NOT EXISTS " + tableName + "(";
    }
    return *this;
}

void SiboSql::init() {
    this->tableQuery.erase(std::prev(this->tableQuery.end()));
    this->tableQuery += ");";
    this->queries.push_back(this->tableQuery);
    this->tableQuery = "";
    for (std::string query:this->queries) {
      //  sqlite3_reset(stmt);
        sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
        sqlite3_step(stmt);
    }
}

SiboSql SiboSql::id() {
    this->tableQuery += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    return *this;
}

void SiboSql::query(std::string query) {
     sqlite3_prepare(db,query.c_str(),-1,&stmt,NULL);
}

void SiboSql::query(std::string query,int (*callback)(void *, int, char **, char **)) {
    sqlite3_exec(db, query.c_str(), callback, 0, NULL);
}

sqlite3_stmt *SiboSql::execute() {
    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf(sqlite3_errmsg(db));
    }

    return stmt;
}

void SiboSql::bind(int index, int value) {
    if (sqlite3_bind_int(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
}

void SiboSql::bind(int index, std::string value) {
    if (sqlite3_bind_text(
            stmt,
            index,
            value.c_str(),
            -1,
            NULL
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
}

void SiboSql::bind(int index, double value) {
    if (sqlite3_bind_double(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
}
//
std::vector<std::map<std::string,char*>> SiboSql::stmtToArray(sqlite3_stmt *Stmt){
    std::vector<std::map<std::string,char*>> indexes;
    while (sqlite3_step(Stmt) != SQLITE_DONE){
        std::map<std::string,char*> Index;
        int columnCounts = sqlite3_column_count(Stmt);
        for(int i = 0; i < columnCounts ; i++){
                char* value = (char *) sqlite3_column_text(Stmt, i);
                Index[sqlite3_column_name(Stmt,i)] = value;
        }
        indexes.push_back(Index);
    }
    return indexes;
}