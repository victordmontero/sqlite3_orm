function(project_tests_Debug)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DSQLITE3_ORM_WIN32
    -DDEBUG
  )

  set(INCLUD_DIRS 
    ../../include
    ../../thirdparty
    ../../../check/out/build
    ../../../check/out/build/src
  )
  include_directories(${INCLUD_DIRS})

  set(LIB_DIRS
    ../../../check/out/build/src/Debug
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    ../../tests/tests.cpp
  )
  add_executable( tests_Debug ${SRC})
  set_target_properties( tests_Debug 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/tests"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/tests"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/tests"
    OUTPUT_NAME  "tests"
  )

  set(LIBS 
    check
  )
  target_link_libraries(tests_Debug ${LIBS})
endfunction(project_tests_Debug)
project_tests_Debug()

function(project_tests_Release)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)

  add_definitions(
    -DSQLITE3_ORM_WIN32
    -DNDEBUG
  )

  set(INCLUD_DIRS 
    ../../include
    ../../thirdparty
    ../../../check/out/build
    ../../../check/out/build/src
  )
  include_directories(${INCLUD_DIRS})

  set(LIB_DIRS
    ../../../check/out/build/src/Release
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    ../../tests/tests.cpp
  )
  add_executable( tests_Release ${SRC})
  set_target_properties( tests_Release 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/tests"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/tests"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/tests"
    OUTPUT_NAME  "tests"
  )

  set(LIBS 
    check
  )
  target_link_libraries(tests_Release ${LIBS})
endfunction(project_tests_Release)
project_tests_Release()
