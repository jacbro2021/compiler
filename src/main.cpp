#include <iostream>

#include "tokenizer.hpp"
#include "parser.hpp"

using namespace std;
using namespace simpleparser;

int main() {
    cout<<"simpleparser 0.1\n"<<endl;

    FILE * fh = fopen("/Users/jsbrown/Developer/compiler-learning/test/test.myc", "r");
    if (!fh) {
        cerr << "Can't find file" << endl;
    }

    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string file_contents(fileSize, ' ');
    fread(file_contents.data(), 1, fileSize, fh);
    
    // cout << file_contents << endl << endl;

    Tokenizer tokenizer;
    vector<Token> tokens = tokenizer.parse(file_contents);

    // for (auto token : tokens) {
    //     token.debugPrint();
    // }

    Parser parser;
    parser.parse(tokens);

    parser.debugPrint();

    return 0;
}