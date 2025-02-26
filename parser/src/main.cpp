#include <iostream>

#include "tokenizer.hpp"
#include "parser.hpp"

using namespace std;
using namespace simpleparser;

int main() {
    try {
        cout<<"simpleparser 0.1\n"<<endl;

        FILE * fh = fopen("/Users/jsbrown/Developer/compiler/parser/test/test.myc", "r");
        if (!fh) {
            cerr << "Can't find file" << endl;
        }

        fseek(fh, 0, SEEK_END);
        size_t fileSize = ftell(fh);
        fseek(fh, 0, SEEK_SET);
        string file_contents(fileSize, ' ');
        fread(file_contents.data(), 1, fileSize, fh);

        Tokenizer tokenizer;
        vector<Token> tokens = tokenizer.parse(file_contents);

        Parser parser;
        parser.parse(tokens);

        parser.debugPrint();
    } catch (exception& err) {
        cerr << "Error: " << err.what() << endl;
        return 2;
    } catch (...) {
        cerr << "Unknown error." << endl;
        return 1;
    }

    return 0;
}
