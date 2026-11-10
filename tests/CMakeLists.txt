
cmake_minimum_required(VERSION 3.22.1)

project(sqlite3_orm_tests)

include_directories(../include)

message("include dirs: ${CMAKE_SOURCE_DIR}")

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)

target_link_libraries(GTest::GTest INTERFACE gtest_main gmock_main)

file(GLOB_RECURSE SQLITE3_ORM_HEADERS
  "../include/*.hpp"
  "../src/*.hpp"
  "../thirdparty/sqlite/*.h*"
)

file(GLOB_RECURSE SQLITE3_ORM_SOURCES
  "../src/*.cpp"
  "../thirdparty/sqlite/*.c*"
)

add_executable(${PROJECT_NAME}
   ${SQLITE3_ORM_HEADERS}
   ${SQLITE3_ORM_SOURCES}
   tests.cpp
)

# add_compile_definitions(DOENGINE_TESTING)

target_link_libraries(${PROJECT_NAME} PRIVATE
    # GTest::gmock
    GTest::GTest
)

#Sql String test######################
add_executable(sqlite3_orm_sql_string_tests
   "../include/string.hpp"
   "../src/string.cpp"
   utSqlString.cpp
)

target_link_libraries(sqlite3_orm_sql_string_tests PRIVATE
    GTest::GTest
)
target_compile_options(sqlite3_orm_sql_string_tests PRIVATE -fsanitize=address,leak)
target_link_options(sqlite3_orm_sql_string_tests PRIVATE -fsanitize=address,leak)


add_test(NAME sqlite3_orm_sql_string_tests
         COMMAND ${CMAKE_COMMAND} -E env
                 LSAN_OPTIONS=verbosity=1:log_threads=1
                 $<TARGET_FILE:sqlite3_orm_sql_string_tests>)

# add_test(NAME sqlite3_orm_sql_string_tests
#          COMMAND sqlite3_orm_sql_string_tests)

set_tests_properties(sqlite3_orm_sql_string_tests PROPERTIES
  ENVIRONMENT "LSAN_OPTIONS=verbosity=1:log_threads=1"
)

#####################################

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

add_test(NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME})

# if(DOENGINE_COVERAGE)
#   message("Compiling with coverage flags")
#   # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
#   # set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
#   # set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
#   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
#   set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -O0")
#   append_coverage_compiler_flags()
#   setup_target_for_coverage_gcovr_html(NAME ${PROJECT_NAME}_cov
#         BASE_DIRECTORY ../
#         EXCLUDE "test/" "build/"
#     )
# endif()