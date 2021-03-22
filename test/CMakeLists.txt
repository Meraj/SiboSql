cmake_minimum_required(VERSION 3.17)
project(SiboSqlTest)
## SQLITE
find_package (SQLite3 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(SiboSqlTest main.cpp ../include/SiboSql.h ../src/SiboSql.cpp)

## SQLITE
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SQLite3_LIBRARIES})