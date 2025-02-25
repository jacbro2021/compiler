#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP

#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

namespace simpleparser {

    using namespace std;

    enum TokenType {
        WHITESPACE,         // No token ever has this type.
        IDENTIFIER,
        INTEGER_LITERAL,
        DOUBLE_LITERAL,
        STRING_LITERAL,
        OPERATOR,
        STRING_ESCAPE_SEQUENCE,
        POTENTIAL_DOUBLE,
        POTENTIAL_COMMENT,
        COMMENT,
    };

    static const char* sTokenTypeStrings[] = {
        "WHITESPACE",         // No token ever has this type
        "IDENTIFIER",
        "INTEGER_LITERAL",
        "DOUBLE_LITERAL",
        "STRING_LITERAL",
        "OPERATOR",
        "STRING_ESCAPE_SEQUENCE",
        "POTENTIAL_DOUBLE",
        "POTENTIAL_COMMENT",
        "COMMENT",
    };

    class Token {
    public:
        enum TokenType mType{WHITESPACE};
        string mText;
        size_t mLineNumber{0};

        /**
        * Convenience debug method to print a parameter definition to stdout.
        */
        void debugPrint() const;
    };

    class Tokenizer {
    public:
        /**
        * Takes in a string reference for all of the source code being compiled.
        * Analyzes the source code turning it into a series of tokens each with one of 
        * the 'TokenTypes'
        *
        * @param inProgram String reference for desired source code.
        * @return array of tokens, each with the proper TokenType. 
        */
        vector<Token> parse(const string &inProgram);

    private:
        void endToken(Token &token, vector<Token> &tokens);
    };
}

#endif 