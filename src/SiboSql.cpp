//
// Created by Meraj on 3/22/2021.
//

#include <functional>
#include "../include/SiboSql.h"

SiboSql::SiboSql() {

}

SiboSql::SiboSql(char* dbName) {
    rc = sqlite3_open(dbName, &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

SiboSql::SiboSql(std::string dbName) {
    rc = sqlite3_open(dbName.c_str(), &db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    }
}

SiboSql SiboSql::column(std::string columnName, std::string dataType) {
    this->tableQuery += columnName + " " + dataType+",";
    return *this;
}

SiboSql SiboSql::table(std::string tableName) {
    if (this->tableQuery.empty()){
        this->tableQuery += "CREATE TABLE IF NOT EXISTS " + tableName + "(";
    }else{
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
    for(std::string query:this->queries){
        std::cout << query << std::endl;
        sqlite3_prepare(db,query.c_str(),-1,&stmt,NULL);
        sqlite3_step(stmt);
    }
}

SiboSql SiboSql::id() {
    this->tableQuery += "id INTEGER PRIMARY KEY AUTOINCREMENT,";
    return *this;
}

sqlite3_stmt* SiboSql::query(std::string query) {
    sqlite3_prepare(db,query.c_str(),-1,&stmt,NULL);
    sqlite3_step(stmt);
    return stmt;
}

void SiboSql::query(std::string query, std::function<int (void*,int,char**,char**)> callback) {
sqlite3_exec(db, query.c_str(), NULL, 0, NULL);

}




