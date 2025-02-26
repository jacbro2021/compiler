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
        Instruction{LOAD_INT, 0, 0},
        Instruction{PUSH_INT, 0, 10},
        Instruction{COMP_INT_LT, 0, 0},
        Instruction{JUMP_BY_IF_ZERO, 0, 10},

        Instruction{PUSH_INT, 0, 4000},
        Instruction{PUSH_INT, 0, 1042},
        Instruction{ADD_INT, 0, 0},
        Instruction{PRINT_INT, 0, 0},

        Instruction{LOAD_INT, 0, 0},
        Instruction{PUSH_INT, 0, 1},
        Instruction{ADD_INT, 0, 0},
        Instruction{STORE_INT, 0, 0},
        Instruction{JUMP_BY, 0, -12},
        Instruction{EXIT, 0, 0},
    };

    BytecodeInterpreter::Run(code);


    cout << "\ndone." << endl;

    return 0;
}