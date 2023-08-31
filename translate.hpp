#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#define ERRCODE_OK           0
#define ERRCODE_GENERIC      1
#define ERRCODE_SYNTAX       2
#define ERRCODE_FILERD       3

#define ERRMSG_OK            "OK"
#define ERRMSG_GENERIC       "Generic Error Encountered"
#define ERRMSG_SYNTAX        "Syntax Error"
#define ERRMSG_FILERD        "File could not be read"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <stack>

using namespace std;

enum VarType {
    INT,
    
};

struct function {

};

struct symbol {
    string symbolName;
    
};

struct TranslationResult {
    int result;
    string resultMsg;
    vector<string> lines;
};

struct LineInfo {
    uint32_t lineNumber;
    string lineText;
};

struct LineParseResult {
    LineInfo line;

    int errorCode;
    string errMsg;
};

enum LineType {
    VAR_ASSIGNMENT;
};

TranslationResult readAll(string filename) {
    vector<string> lines;
    TranslationResult tr;
    ifstream tsl_file(filename);
    if(not tsl_file.is_open()) {
        tr.result = ERRCODE_FILERD;
        return tr;
    }
    string line;
    while(tsl_file) {
        std::getline(tsl_file, line);
        lines.push_back(line);
    }
    tr.result = ERRCODE_OK;
    tr.lines = lines;
    return tr;
}

void unwrapStack(stack<LineInfo> stackTrace) {
    if(not stackTrace.size()){
        return;
    }
    LineInfo stackTop = stackTrace.top();
    stackTrace.pop();
    unwrapStack(stackTrace, lpr);
    cerr << " " << "Within body on " << stackTop.lineNumber << endl << "    " << stackTop.lineText << endl;
}

void writeError(stack<LineInfo> stackTrace, LineParseResult lpr) {
    cerr << "Encountered error! Producing stack trace:" << endl;
    unwrapStack(stackTrace);
    cerr << "ERROR: Line " << lpr.line.lineNumber << ": " << lpr.line.lineText << endl;
}

LineParseResult parseLine(LineInfo li,
                          map<string, symbol>& symbols, 
                          map<string, function>& functions) {
    LineParseResult lpr;
    lpr.line = li;
    
}

TranslationResult buildScript(vector<string> scriptLines, bool debug){
    /* REQUIRED
    -> stack for encapsulation layers
    -> symbol table for variable definitions
    -> function table for function definitions
    -> in-order operator execution
    */

    //variable creation
    //variable assignment
    //if statement
    //for loop
    //while loop
    //function definition
    //inline conditionals
    //return values
    //operators (+ - * / < > << >> ? : & && % ! ** = == () [] | ||)
    //builtin function
    TranslationResult tr;
    stack<LineInfo> codeStack;
    vector<string> translatedLines;

    map<string, symbol> symbols;
    map<string, function> functions;

    for(unsigned int lineIdx = 0; lineIdx < scriptLines.size(); ++lineIdx){
        LineInfo li;
        li.lineNumber = lineIdx;
        li.lineText = scriptLines[lineIdx];
        LineParseResult lpr = parseLine(li, &symbols, &functions);
        if(lpr.errorCode != ERRCODE_OK){
            cerr << "Encountered an error:" << endl;
            writeError(codeStack, lpr);
        }
    }

    cout << "SYMBOLS:" << endl;
    for(auto it = symbols.begin(); it != symbols.end(); ++it) {
        cout << it->first << " = " << symbol_str(it->second) << endl;
    }
    cout << endl;
    
    cout << "FUNCTIONS:" << endl;
    for(auto it = functions.begin(); it != functions.end(); ++it) {
        cout << it->first << " = " << func_str(it->second) << endl;
    } 

    return tr;
}

int translateAndWrite(string filename, bool debug) {
    cout << "FILENAME: " << filename << endl;
    cout << " - DEBUG = " << (debug ? "true" : "false") << endl;

    TranslationResult tr = readAll(filename);
    if(tr.result != ERRCODE_OK) {
        cerr << "File could not be read: " << tr.result << endl;
        return tr.result;
    }

    cout << endl;

    tr = buildScript(tr.lines);
    if(tr.result != ERRCODE_OK) {
        //TODO
    }

    return 0;
}

#endif