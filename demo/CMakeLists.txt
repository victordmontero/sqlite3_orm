
cmake_minimum_required(VERSION 3.22.1)

project(sqlite3_orm_demo)

message("include dirs: ${CMAKE_SOURCE_DIR}")

add_executable(${PROJECT_NAME}
   main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ../include)

target_link_libraries(${PROJECT_NAME} PRIVATE
  sqlite3_orm
)
