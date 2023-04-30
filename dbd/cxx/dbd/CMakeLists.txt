cmake_minimum_required(VERSION 3.0)
project(dbd)

add_library(dbd
  src/dbd_lexer.cpp include/dbd_lexer.hpp
  src/dbd_parser.cpp include/dbd_parser.hpp
)
set_property(TARGET dbd PROPERTY CXX_STANDARD 20)
target_include_directories(dbd PUBLIC include)