function(project_sqlite3_orm_Debug)
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

  set(LIB_DIRS
    ../../thirdparty
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    ../../include/constants.hpp
    ../../include/constraints.hpp
    ../../include/database.hpp
    ../../include/enums.hpp
    ../../include/log.hpp
    ../../include/parse.hpp
    ../../include/sqlite3_orm.hpp
    ../../include/string.hpp
    ../../include/tableresult.hpp
    ../../src/constraints.cpp
    ../../src/database.cpp
    ../../src/log.cpp
    ../../src/string.cpp
    ../../src/tableresult.cpp
    ../../premake5.lua
    ../../premake5EVO.lua
  )
  add_library( sqlite3_orm_Debug STATIC ${SRC})
  set_target_properties( sqlite3_orm_Debug 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/lib"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/lib"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Debug/lib"
    OUTPUT_NAME  "sqlite3_orm"
  )

  set(LIBS 
    sqlite3d
  )
  target_link_libraries(sqlite3_orm_Debug ${LIBS})
endfunction(project_sqlite3_orm_Debug)
project_sqlite3_orm_Debug()

function(project_sqlite3_orm_Release)
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

  set(LIB_DIRS
    ../../thirdparty
  )
  link_directories(${LIB_DIRS})

  set(SRC 
    ../../include/constants.hpp
    ../../include/constraints.hpp
    ../../include/database.hpp
    ../../include/enums.hpp
    ../../include/log.hpp
    ../../include/parse.hpp
    ../../include/sqlite3_orm.hpp
    ../../include/string.hpp
    ../../include/tableresult.hpp
    ../../src/constraints.cpp
    ../../src/database.cpp
    ../../src/log.cpp
    ../../src/string.cpp
    ../../src/tableresult.cpp
    ../../premake5.lua
    ../../premake5EVO.lua
  )
  add_library( sqlite3_orm_Release STATIC ${SRC})
  set_target_properties( sqlite3_orm_Release 
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/lib"
    LIBRARY_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/lib"
    RUNTIME_OUTPUT_DIRECTORY "C:/Users/vmontero/Documents/Proyectos/sqlite3_orm/bin/Release/lib"
    OUTPUT_NAME  "sqlite3_orm"
  )

  set(LIBS 
    sqlite3
  )
  target_link_libraries(sqlite3_orm_Release ${LIBS})
endfunction(project_sqlite3_orm_Release)
project_sqlite3_orm_Release()
