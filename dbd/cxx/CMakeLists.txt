cmake_minimum_required(VERSION 3.0)
project(dbd)

Include(FetchContent)

set(DBD_BUILD_TESTS OFF CACHE BOOL "If dbd should build the automatic test suite")

add_subdirectory(dbd)
add_subdirectory(dbd2md)
if(${DBD_BUILD_TESTS})
  add_subdirectory(test)
endif()