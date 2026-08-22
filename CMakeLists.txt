cmake_minimum_required(VERSION 4.2.3)

project(sqlite3_orm)

# --- sqlite3_orm (StaticLib) ---
# Matches the premake project("sqlite3_orm"):
#   - kind StaticLib
#   - cppdialect C++98
#   - targetdir bin/<cfg>/lib
#   - sources: include/**/*.hpp, src/**/*.hpp, src/**/*.cpp, thirdparty/sqlite/**.*
#   - undefines: SQLITE3_ORM_EVO
#   - includedirs: include, thirdparty/sqlite
#   - filter defines: DEBUG/NDEBUG, SQLITE3_ORM_WIN32 on Win32/Win64, LINUX on Linux
#   - pic("On") -> set POSITION_INDEPENDENT_CODE ON

option(SQLITE3_ORM_TESTS "Compiles and runs tests" OFF)
option(SQLITE3_ORM_DEMO "Compiles demo" OFF)

file(GLOB_RECURSE SQLITE3_ORM_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite/*.h*"
)

file(GLOB_RECURSE SQLITE3_ORM_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite/*.c*"
)

add_library(sqlite3_orm STATIC ${SQLITE3_ORM_HEADERS} ${SQLITE3_ORM_SOURCES})

# premake was C++98
target_compile_features(sqlite3_orm PRIVATE cxx_std_98)
set_target_properties(sqlite3_orm PROPERTIES
  CXX_STANDARD 98
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
  POSITION_INDEPENDENT_CODE ON
)

target_include_directories(sqlite3_orm PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/sqlite"
)

# undefines({ "SQLITE3_ORM_EVO" })
target_compile_definitions(sqlite3_orm PRIVATE SQLITE3_ORM_EVO=0)

# Debug/Release defines like premake
target_compile_definitions(sqlite3_orm PRIVATE
  $<$<CONFIG:Debug>:DEBUG>
  $<$<CONFIG:Release>:NDEBUG>
)

# Platform defines
if (WIN32)
  target_compile_definitions(sqlite3_orm PRIVATE SQLITE3_ORM_WIN32)
  if (CMAKE_SIZEOF_VOID_P EQUAL 4)
    target_compile_definitions(sqlite3_orm PRIVATE WIN32)
  else()
    target_compile_definitions(sqlite3_orm PRIVATE WIN64)
  endif()
  # premake used system(windows) and architecture x86/x86_64; CMake toolchain handles arch.
else()
  target_compile_definitions(sqlite3_orm PRIVATE LINUX)
endif()

# targetdir("bin/%{cfg.buildcfg}/lib")
# Put the archive where your other targets expect it:
# set(sqlite3_orm_out_dir
#   "${CMAKE_CURRENT_SOURCE_DIR}/extlib/sqlite3_orm/bin/${PM_PLATFORM}/$<CONFIG>/lib"
# )
# set_target_properties(sqlite3_orm PROPERTIES
#   ARCHIVE_OUTPUT_DIRECTORY "${sqlite3_orm_out_dir}"
#   LIBRARY_OUTPUT_DIRECTORY "${sqlite3_orm_out_dir}"
#   RUNTIME_OUTPUT_DIRECTORY "${sqlite3_orm_out_dir}"
# )

# If you truly need the exact layout from premake:
# extlib/sqlite3_orm/bin/<cfg.buildcfg>/lib
# then use:
# set(sqlite3_orm_out_dir
#   "${CMAKE_CURRENT_SOURCE_DIR}/extlib/sqlite3_orm/bin/$<CONFIG>/lib"
# )
# and replace the set_target_properties above.

if(SQLITE3_ORM_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

if(SQLITE3_ORM_DEMO)
    add_subdirectory(demo)
endif()
