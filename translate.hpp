#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#define OK             0
#define GENERIC_ERROR  1<<0
#define SYNTAX_ERROR   1<<1
// #define 

#include <iostream>

using namespace std;

int translateAndWrite(string filename, bool debug) {
    cout << "FILENAME: " << filename << endl;
    cout << " - DEBUG = " << (debug ? "true" : "false") << endl;
    return 0;
}

#endif