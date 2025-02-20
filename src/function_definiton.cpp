#include <iostream>

#include "function_definition.hpp"

namespace simpleparser {
    void FunctionDefintion::debugPrint() {
        cout << mName <<"(\n";

        for (ParameterDefinition param : mParameters) {
            param.debugPrint();
        }

        cout << ") {\n";

        for (auto statement : mStatements) {
            statement.debugPrint();
        }

        cout << "}" << endl;
    }

    void ParameterDefinition::debugPrint() {
        cout << mType.mName << " " << mName << endl;
    }
}