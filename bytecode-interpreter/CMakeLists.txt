cmake_minimum_required(VERSION 3.17)
project(bytecodeinterpreter)
set(CMAKE_CXX_STANDARD 20)

add_library(bytecode_interpreter_internals 
            src/bytecode_interpreter.cpp 
            include/bytecode_interpreter.hpp 
            include/instruction.hpp) 
target_include_directories(bytecode_interpreter_internals PUBLIC include)

add_executable(bytecodeinterpreter main.cpp)
target_link_libraries(bytecodeinterpreter bytecode_interpreter_internals)