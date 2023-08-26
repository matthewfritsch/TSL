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

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;

struct TranslationResult {
    int result;
    string result_msg;
    vector<string> lines;
};

struct LineInfo {
    uint32_t lineNumber;
    string lineText;
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

TranslationResult buildScript(vector<string> scriptLines){
    TranslationResult tr;
    stack<LineInfo> codeStack;
    vector<string> translatedLines;
    for(unsigned int lineIdx = 0; lineIdx < scriptLines.size(); ++lineIdx){
        LineInfo li;
        li.lineNumber = lineIdx;
        li.lineText = scriptLines[lineIdx];
        LineParseResult lpr = parseLine(li);
        if(lpr.errorCode != ERRCODE_OK){
            unwrapStack(codeStack);
        }
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