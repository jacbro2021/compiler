#include <iostream>

#include "statement.hpp"

namespace simpleparser {
    void Statement::debugPrint(size_t indent) {
        cout << string(indent, '\t') << sStatementKindStrings[int(mKind)] << " ";
        cout << mType.mName << " " << mName << " (\n";
        for (Statement statement : mParameters) {
            statement.debugPrint(indent + 1);
        }
        cout << string(indent, '\t') << ")" << endl;
    }
}