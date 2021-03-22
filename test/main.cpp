#include <iostream>
#include "../SiboSql/include/SiboSql.h"
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
    sqlite3_stmt* stmt ;
    siboSql.query("INSERT INTO persons (first_name,last_name) VALUES ('jafar','jafarian')"); // insert data
    stmt = siboSql.query("SELECT * FROM persons"); // select data
    siboSql.query("SELECT * FROM persons",callback); // with callback function
}
