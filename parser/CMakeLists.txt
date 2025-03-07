cmake_minimum_required(VERSION 3.17)
project(parser)
set(CMAKE_CXX_STANDARD 20)

add_library(parser_internals 
            src/function_definiton.cpp 
            include/function_definition.hpp
            src/parser.cpp 
            include/parser.hpp
            src/statement.cpp 
            include/statement.hpp
            src/tokenizer.cpp 
            include/tokenizer.hpp
)
target_include_directories(parser_internals PUBLIC include)

add_executable(parser main.cpp)
target_link_libraries(parser parser_internals)