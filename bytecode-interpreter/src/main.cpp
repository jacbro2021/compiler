#include <iostream>
#include <vector>

#include "instruction.hpp"
#include "bytecode_interpreter.hpp"

using namespace std;
using namespace bytecodeinterpreter;

int main(int argc, char ** argv) {
    // Not using right now.
    (void) argc;
    (void) argv;

    cout << "bytecodeinterpreter 1.0\n" << endl;

    Instruction code[] = {
        Instruction{PUSH_INT, 0, 0},
        Instruction{LOAD_INT_BASEPOINTER_RELALTIVE, 0, 0},
        Instruction{LOAD_INT_BASEPOINTER_RELALTIVE, 0, -2},
        Instruction{COMP_INT_LT, 0, 0},
        Instruction{JUMP_BY_IF_ZERO, 0, 10},

        Instruction{PUSH_INT, 0, 4000},
        Instruction{PUSH_INT, 0, 1042},
        Instruction{ADD_INT, 0, 0},
        Instruction{PRINT_INT, 0, 0},

        Instruction{LOAD_INT_BASEPOINTER_RELALTIVE, 0, 0},
        Instruction{PUSH_INT, 0, 1},
        Instruction{ADD_INT, 0, 0},
        Instruction{STORE_INT_BASEPOINTER_RELATIVE, 0, 0},
        Instruction{JUMP_BY, 0, -12},

        Instruction{PUSH_INT, 0, 0},
        Instruction{LOAD_INT_BASEPOINTER_RELALTIVE, 0, -2},
        Instruction{COMP_INT_LT, 0, 0},
        Instruction{JUMP_BY_IF_ZERO, 0, 8},
        Instruction{PUSH_INT, 0, 0},
        Instruction{LOAD_INT_BASEPOINTER_RELALTIVE, 0, -2},
        Instruction{PUSH_INT, 0, -1},
        Instruction{ADD_INT, 0, 0},
        Instruction{CALL, 0, -22},
        Instruction{POP_INT, 0, 0},
        Instruction{POP_INT, 0, 0},


        Instruction{PUSH_INT, 0, 42},
        Instruction{STORE_INT_BASEPOINTER_RELATIVE, 0, -3},
        Instruction{JUMP_BY, 0, 1},
        Instruction{POP_INT, 0, 0},
        Instruction{RETURN, 0, 0},
    };

    int16_t resultValue = 0;
    BytecodeInterpreter::Run(code, { 3 }, &resultValue);

    cout << "\nResult:  " << resultValue << "\ndone." << endl;

    return 0;
}