cmake_minimum_required(VERSION 3.0)
project(dbd2md)

include(FetchContent)

FetchContent_Declare(
    fmt 
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        9.1.0
  )
FetchContent_MakeAvailable(fmt)

add_executable(dbd2md dbd2md.cpp)
target_link_libraries(dbd2md dbd fmt)
set_property(TARGET dbd2md PROPERTY CXX_STANDARD 20)

target_compile_definitions(dbd2md PUBLIC OUTPUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../../docs/dbc")
target_compile_definitions(dbd2md PUBLIC INPUT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../WoWDBDefs/definitions")
target_compile_definitions(dbd2md PUBLIC COMMENTS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../../comments")

add_custom_target(dbd2md_run COMMAND dbd2md)
add_dependencies(dbd2md_run dbd2md)