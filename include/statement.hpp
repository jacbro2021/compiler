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
        LITERAL
    };

    static const char* sStatementKindStrings[] = {
        "VARIABLE_DECLARATION",
        "FUNCTION_CALL", 
        "LITERAL"
    };

    class Statement {
    public: 
        string mName;
        Type mType{Type("void", VOID)};
        vector<Statement> mParameters;
        StatementKind mKind{StatementKind::FUNCTION_CALL};

        void debugPrint();
    };
};

#endif