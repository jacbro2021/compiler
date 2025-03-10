#ifndef PARSER_HPP
#define PARSER_HPP

#include <optional>
#include <string>
#include <map>

#include "tokenizer.hpp"
#include "type.hpp"
#include "function_definition.hpp"
#include "statement.hpp"

namespace simpleparser {
    using namespace std;

    class Parser {
    public:
        Parser();

        /**
        * Parses an array of tokens, checks their validity, and stores them into various
        * properties in this object.  
        *
        * @param tokens Reference to an array of tokens from the lexer.
        */
        void parse(vector<Token> &tokens);
        
        /**
        * Convenience debug method to print all parsed objects to stdout.
        */
        void debugPrint();

    private:
        vector<Token>::iterator mCurrentToken;
        vector<Token>::iterator mEndToken;
        map<string, Type> mTypes;
        map<string, FunctionDefintion> mFunctions;

        bool expectFunctionDefintion();

        optional<Token> expectIdentifier(const string &name = string());
        optional<Token> expectOperator(const string &name = string());
        optional<Type> expectType();
        optional<Statement> expectOneValue();
        optional<Statement> expectVariableDeclaration();
        optional<Statement> expectFunctionCall();
        optional<vector<Statement>> parseFunctionBody();
        optional<Statement> expectStatement();
        optional<Statement> expectExpression();

        size_t operatorPrecedence(const string &operatorName);
        Statement* findRightmostStatement(Statement *lhs, size_t rhsPrecedence);
    };

}

#endif