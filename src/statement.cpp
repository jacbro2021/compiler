#include <iostream>

#include "statement.hpp"

namespace simpleparser {
    void Statement::debugPrint() {
        cout << sStatementKindStrings[int(mKind)] << " ";
        cout << mType.mName << " " << mName << " (\n";
        for (Statement statement : mParameters) {
            statement.debugPrint();
        }
        cout << ")" << endl;
    }
}