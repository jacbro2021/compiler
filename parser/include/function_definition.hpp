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

        /**
        * Convenience debug method to print a parameter definition to stdout.
        *
        * @param indent The indentation that the parameter should be printed at.
        */
        void debugPrint(size_t indent) const;
    };

    class FunctionDefintion {
    public:
        string mName;
        vector<ParameterDefinition> mParameters;
        vector<Statement> mStatements;

        /**
        * Convenience debug method to print a function definition to stdout.
        */
        void debugPrint();
    };
}

#endif