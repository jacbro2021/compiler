#include <iostream>

#include "function_definition.hpp"

namespace simpleparser {
    void FunctionDefintion::debugPrint() {
        cout << mName <<"(\n";

        for (ParameterDefinition param : mParameters) {
            param.debugPrint(1);
        }

        cout << ") {\n";

        for (auto statement : mStatements) {
            statement.debugPrint(0);
        }

        cout << "}" << endl;
    }

    void ParameterDefinition::debugPrint(size_t indent) const {
        cout << string(indent, '\t') << mType.mName << " " << mName << endl;
    }
}