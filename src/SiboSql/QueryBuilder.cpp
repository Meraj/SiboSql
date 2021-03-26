//
// Created by Meraj on 3/24/2021.
//

#include "../../include/SiboSql/QueryBuilder.h"

QueryBuilder::QueryBuilder(sqlite3 *db) {
this->db = db;
}
// Select :
QueryBuilder QueryBuilder::select(std::string column) {
    this->select_statement = std::move(column);
    return *this;
}
QueryBuilder QueryBuilder::select(const std::vector<std::string>& columns) {
    this->select_statement.clear();
    for(const std::string& column:columns)
        this->select_statement += column+",";
    this->select_statement.pop_back();
    return *this;
}
QueryBuilder QueryBuilder::selectRaw(std::string selectRaw) {
   return this->select(std::move(selectRaw));
}
QueryBuilder QueryBuilder::addSelect(std::string column) {
    this->select_statement+=","+std::move(column);
}
// End Select


sqlite3_stmt *QueryBuilder::insert(std::vector<std::string> columns, std::vector<std::string> values) {
    this->bindParamsVector = std::move(values);
     this->buildQuery(INSERT);
}

std::string QueryBuilder::buildQuery(int type) {

}

QueryBuilder QueryBuilder::table(std::string table) {
    this->Table_str = std::move(table);

    return *this;
}

std::string QueryBuilder::buildQuery(int type, std::vector<std::string> columns, std::vector<std::string> values) {
    std::string query_str;
    switch (type) {
        case 0: {
            query_str.append("INSERT INTO ").append(this->Table_str).append(" (");
            for (std::string column:columns)
                query_str.append(column).append(",");
            query_str.pop_back();
            query_str.append(") ").append(" VALUES ").append("(");
            if (this->doBind) {
                for (std::string value:values)
                    query_str.append("?,");
                this->bindParamsVector = std::move(values);
            } else {
                for (std::string value:values)
                    query_str.append(value).append(",");
            }
            query_str.pop_back();
            query_str.append(")");
            return query_str;
        }
            break;
        case 1:

            break;
    }
}

sqlite3_stmt * QueryBuilder::execute(std::string query) {
    sqlite3_prepare(db, query.c_str(), -1, &stmt, NULL);
    if(!this->bindParamsVector.empty()){
        for (int i = 1; i <= this->bindParamsVector.size() ; i++)
            this->bind(i,this->bindParamsVector[i]);
        this->bindParamsVector.clear();
    }
    sqlite3_step(stmt);
    return stmt;
}

 // BIND
void QueryBuilder::bind(int index, int value) {
    if (sqlite3_bind_int(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
}

void QueryBuilder::bind(int index, std::string value) {
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

void QueryBuilder::bind(int index, double value) {
    if (sqlite3_bind_double(
            stmt,
            index,
            value
    )
        != SQLITE_OK) {
        printf("\nCould not bind int.\n");
    }
}

