function(project_demo_Debug)
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
  )
  include_directories(${INCLUD_DIRS})

  set(SRC 
    ../../demo/main.cpp
  )
  add_executable( demo_Debug ${SRC})
  set_target_properties( demo_Debug 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/demo"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/demo"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/demo"
    OUTPUT_NAME  "demo"
  )
endfunction(project_demo_Debug)
project_demo_Debug()

function(project_demo_Release)
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
  )
  include_directories(${INCLUD_DIRS})

  set(SRC 
    ../../demo/main.cpp
  )
  add_executable( demo_Release ${SRC})
  set_target_properties( demo_Release 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/demo"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/demo"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/demo"
    OUTPUT_NAME  "demo"
  )
endfunction(project_demo_Release)
project_demo_Release()
