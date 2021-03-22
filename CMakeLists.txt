cmake_minimum_required(VERSION 3.17)
project(SiboSql)

set(CMAKE_CXX_STANDARD 20)

## SQLITE
find_package (SQLite3 REQUIRED)

add_library(SiboSql src/SiboSql.cpp include/SiboSql.h)

## SQLITE
include_directories(${SQLite3_INCLUDE_DIRS})
target_link_libraries (${PROJECT_NAME} ${SQLite3_LIBRARIES})