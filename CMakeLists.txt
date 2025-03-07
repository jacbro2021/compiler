cmake_minimum_required(VERSION 3.17)
project(parserandcompiler)

set(CMAKE_CXX_STANDARD 20)

add_executable(parserandcompiler main.cpp)

add_subdirectory(parser)
target_link_libraries(parserandcompiler parser_internals)

add_subdirectory(bytecode-interpreter)
target_link_libraries(parserandcompiler bytecode_interpreter_internals)