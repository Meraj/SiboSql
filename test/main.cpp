#include <iostream>
#include "../SiboSql/include/SiboSql.h"
int main() {
    std::string dbName = "testdb.db";
    SiboSql siboSql = SiboSql(dbName);
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
}
