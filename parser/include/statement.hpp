#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <string>
#include <vector>

#include "type.hpp"

namespace simpleparser {
    using namespace std;

    enum class StatementKind: int {
        VARIABLE_DECLARATION,
        FUNCTION_CALL, 
        LITERAL,
        OPERATOR_CALL,
    };

    static const char* sStatementKindStrings[] = {
        "VARIABLE_DECLARATION",
        "FUNCTION_CALL", 
        "LITERAL",
        "OPERATOR_CALL"
    };

    class Statement {
    public: 
        string mName;
        Type mType{Type("void", VOID)};
        vector<Statement> mParameters;
        StatementKind mKind{StatementKind::FUNCTION_CALL};

        /**
        * Convenience debug method to print a parameter definition to stdout.
        *
        * @param indent The indentation that the parameter should be printed at.
        */
        void debugPrint(size_t indent);
    };
};

#endif