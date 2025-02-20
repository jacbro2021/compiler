#ifndef FUNCTION_DEFINITION_HPP
#define FUNCTION_DEFINITION_HPP

#include <string>
#include <vector>

#include "type.hpp"
#include "statement.hpp"

namespace simpleparser {
    using namespace std; 

    class ParameterDefinition {
    public:
        string mName; // Empty string means no name given. 
        Type mType;

        void debugPrint();
    };

    class FunctionDefintion {
    public:
        string mName;
        vector<ParameterDefinition> mParameters;
        vector<Statement> mStatements;

        void debugPrint();
    };
}

#endif