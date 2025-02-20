#include <parser.hpp>

namespace simpleparser {

    Parser::Parser() {
        mTypes["void"] = Type("void", VOID);
        mTypes["int"] = Type("int", INT32);
        mTypes["unsigned"] = Type("unsigned int", UINT32);
        mTypes["char"] = Type("signed char", INT8);
        mTypes["uint8_t"] = Type("uint8_t", UINT8);
        mTypes["double"] = Type("double", DOUBLE); 
    }
    
    void Parser::parse(vector<Token> &tokens) {
        mEndToken = tokens.end();
        mCurrentToken = tokens.begin();

        while (mCurrentToken != tokens.end()) {
            if (expectFunctionDefintion()) {

            } else {
                cerr << "Unknown identifier: " << mCurrentToken->mText << endl;
                ++mCurrentToken;
            }
        }
    }

    bool Parser::expectFunctionDefintion() {
        vector<Token>::iterator parseStart = mCurrentToken;

        optional<Type> possibleType = expectType();

        if (possibleType.has_value()) { 
            optional<Token> possibleName = expectIdentifier();

            if (possibleName.has_value()) {
                optional<Token> possibleOperator = expectOperator("(");

                if (possibleOperator.has_value()) {
                   
                    FunctionDefintion func;
                    func.mName = possibleName->mText;

                    cout << "we have a function: \"" << possibleName->mText << "\"." << endl;

                    while(!expectOperator(")").has_value()) {
                        optional<Type> possibleParamType = expectType();
                        if (!possibleParamType.has_value()) {
                            throw runtime_error("Expected a type at start of argument list.");
                        }
                        optional<Token> possibleVariableName = expectIdentifier();

                        ParameterDefinition param;
                        param.mType = possibleParamType->mName;
                        if (possibleVariableName.has_value()) {
                            param.mName = possibleVariableName->mText ;
                        }

                        func.mParameters.push_back(param);

                        if (expectOperator(")").has_value()) {
                            break;
                        }

                        if (!expectOperator(",").has_value()) {
                            throw runtime_error("Expected ',' to separate parameters or ')' to indicate end of argument list.");
                            break;
                        }
                    }

                    optional<vector<Statement>> statements = parseFunctionBody();
                    if (!statements.has_value()) {
                        mCurrentToken = parseStart;
                        return false;
                    }
                    func.mStatements.insert(func.mStatements.begin(), statements->begin(), statements->end());

                    mFunctions[func.mName] = func;

                    return true; 

                } else {
                    mCurrentToken = parseStart;
                }
            } else {
                mCurrentToken = parseStart;
            }
        }
        
        return false;
    }

    optional<Token> Parser::expectIdentifier(const string &name) {
        if (mCurrentToken == mEndToken) { return nullopt; }
        if (mCurrentToken->mType != IDENTIFIER) { return nullopt; }
        if (!name.empty() && mCurrentToken->mText != name) { return nullopt; }

        Token returnToken = *mCurrentToken;
        ++mCurrentToken;
        return returnToken;
    }

    optional<Token> Parser::expectOperator(const string &name) {
        if (mCurrentToken == mEndToken) { return nullopt; }
        if (mCurrentToken->mType != OPERATOR) { return nullopt; }
        if (!name.empty() && mCurrentToken->mText != name) { return nullopt; }

        Token returnToken = *mCurrentToken;
        ++mCurrentToken;
        return returnToken;
    }

    optional<Type> Parser::expectType() {
        optional<Token> possibleType = expectIdentifier();
        if (!possibleType) { return nullopt; }

        map<string, Type>::iterator foundType = mTypes.find(possibleType->mText);
        if (foundType == mTypes.end()) { 
            --mCurrentToken;
            return nullopt; 
        }

        return foundType->second;
    }    

    optional<vector<Statement>> Parser::parseFunctionBody() {
        if (!expectOperator("{").has_value()) {
            return nullopt;
        }

        vector<Statement> statements;

        while (!expectOperator("}").has_value()) {
            optional<Statement> statement = expectOneValue();
            if (statement.has_value()) {
                statements.push_back(statement.value());
            } 

            if (!expectOperator(";").has_value()) {
                throw runtime_error("Expected ';' at end of statement.");
            }
        }

        return statements;
    }

    optional<Statement> Parser::expectOneValue() {
        optional<Statement> result;
        if (mCurrentToken != mEndToken && mCurrentToken->mType == DOUBLE_LITERAL) {
            Statement doubleLiteralStatement;
            doubleLiteralStatement.mKind = StatementKind::LITERAL;
            doubleLiteralStatement.mName = mCurrentToken->mText;
            doubleLiteralStatement.mType = Type("double", DOUBLE);
            result = doubleLiteralStatement;
            ++mCurrentToken;
        } else if (mCurrentToken != mEndToken && mCurrentToken->mType == INTEGER_LITERAL) {
            Statement integerLiteralStatement;
            integerLiteralStatement.mKind = StatementKind::LITERAL;
            integerLiteralStatement.mName = mCurrentToken->mText;
            integerLiteralStatement.mType = Type("signed integer", INT32);
            result = integerLiteralStatement;
            ++mCurrentToken;  
        } else if (mCurrentToken != mEndToken && mCurrentToken->mType == STRING_LITERAL) {
            Statement stringLiteralStatement;
            stringLiteralStatement.mKind = StatementKind::LITERAL;
            stringLiteralStatement.mName = mCurrentToken->mText;
            stringLiteralStatement.mType = Type("string", UINT8);
            result = stringLiteralStatement;
            ++mCurrentToken;   
        } else {
            result = expectVariableDeclaration();
        }

        if (!result.has_value()) {
            result = expectFunctionCall();
        }
        
        return result;
    }

    optional<Statement> Parser::expectVariableDeclaration() {
        vector<Token>::iterator startToken = mCurrentToken;

        optional<Type> possibleType = expectType();
        if (!possibleType.has_value()) {
            mCurrentToken = startToken;
            return nullopt;
        }

        optional<Token> possibleVariableName = expectIdentifier();
        if (!possibleVariableName.has_value()) {
            mCurrentToken = startToken;
            return nullopt;
        }

        Statement statement;
        statement.mKind = StatementKind::VARIABLE_DECLARATION;
        statement.mName = possibleVariableName->mText;
        statement.mType = possibleType.value();

        if (expectOperator("=").has_value()) {
            optional<Statement> initialValue = expectOneValue();
            if (!initialValue.has_value()) {
                throw runtime_error("Expected initial value to the right of '=' in variable declaration.");
            }

            statement.mParameters.push_back(initialValue.value());
        }

        return statement;
    }

    optional<Statement> Parser::expectFunctionCall() {
        vector<Token>::iterator startToken = mCurrentToken;

        optional<Token> possibleFunctionName = expectIdentifier();
        if (!possibleFunctionName.has_value()) {
            mCurrentToken = startToken;
            return nullopt;
        }

        if (!expectOperator("(").has_value()) {
            mCurrentToken = startToken;
            return nullopt;
        }

        Statement functionCall;
        functionCall.mKind = StatementKind::FUNCTION_CALL;
        functionCall.mName = possibleFunctionName->mText;

        while (!expectOperator(")").has_value()) {
            optional<Statement> parameter = expectOneValue();
            if (!parameter.has_value()) {
                throw runtime_error("Expected expression as parameter");
            } 
            functionCall.mParameters.push_back(parameter.value());

            if (expectOperator(")").has_value()) {
                break;
            } 

            if (!expectOperator(",").has_value()) {
                throw runtime_error("Expected ',' to separate parameters.");
            }
        }

        return functionCall;
    }

    void Parser::debugPrint() {
        for (auto funcPair : mFunctions) {
            funcPair.second.debugPrint();
        }
    }
}