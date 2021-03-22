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

SiboSql SiboSql::query(std::string query) {
     sqlite3_prepare(db,query.c_str(),-1,&stmt,NULL);
    return *this;
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

SiboSql SiboSql::bind(int index, int value) {
    if (sqlite3_bind_int(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
    return *this;
}

SiboSql SiboSql::bind(int index, std::string value) {
    this->bind(index, value.c_str());
    return *this;
}

SiboSql SiboSql::bind(int index, char value) {
    if (sqlite3_bind_text(
            stmt,
            index,
            &value,
            -1,
            NULL
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
    return *this;
}

SiboSql SiboSql::bind(int index, double value) {
    if (sqlite3_bind_double(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
    return *this;
}
