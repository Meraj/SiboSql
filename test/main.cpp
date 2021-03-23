#include <iostream>
#include "../include/SiboSql.h"
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}
int main() {
    std::string dbName = "testdb.db";
    // Create Database
    SiboSql siboSql = SiboSql(dbName); // open or Create (if does not exist)
    siboSql.table("persons")
    .id()
    .column("first_name","VARCHAR")
    .column("last_name","VARCHAR")
    .table("jobs")
    .column("job_title","VARCHAR")
    .column("job_id","INTEGER")
    .table("workers")
    .column("name","VARCHAR")
    .column("user_id","INTEGER")
    .init();
    // End Create Database
    // insert data and bind params (Prevent Sql Injection)
    siboSql.query("INSERT INTO persons (first_name,last_name) VALUES (?,?);");
    siboSql.bind(1, "jafar");
    siboSql.bind(2,"jafarian");
    siboSql.execute();
    // END insert data and bind params
    // insert data normally
    siboSql.query("INSERT INTO persons (first_name,last_name) VALUES ('mamad','mamadian');");
    siboSql.execute();
    // select data
    sqlite3_stmt *stmt;
    siboSql.query("SELECT * FROM persons");
    stmt = siboSql.execute(); // handle stmt your self


    siboSql.query("SELECT * FROM persons",callback); // with callback function

}
