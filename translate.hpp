#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP

#define ERR_OK             0
#define ERR_GENERIC_ERROR  1
#define ERR_SYNTAX_ERROR   2
#define ERR_FILE_ERROR     3

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct FileResult {
    int result;
    vector<string> lines;
};

FileResult readAll(string filename) {
    vector<string> lines;
    FileResult fr;
    ifstream tsl_file(filename);
    if(not tsl_file.is_open()) {
        fr.result = ERR_FILE_ERROR;
        return fr;
    }
    string line;
    while(tsl_file) {
        std::getline(tsl_file, line);
        lines.push_back(line);
    }
    fr.result = ERR_OK;
    fr.lines = lines;
    return fr;
}

int translateAndWrite(string filename, bool debug) {
    cout << "FILENAME: " << filename << endl;
    cout << " - DEBUG = " << (debug ? "true" : "false") << endl;

    FileResult fr = readAll(filename);
    if(fr.result != ERR_OK) {
        cerr << "File could not be read: " << fr.result << endl;
        return fr.result;
    }

    cout << endl;
    cout << "- BEGIN CONTENTS -" << endl;
    for(string s : fr.lines) {
        cout << s << endl;
    }
    cout << "-  END CONTENTS  -" << endl;

    return 0;
}

#endif