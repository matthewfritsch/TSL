#include <iostream>
#include <vector>

#include "translate.hpp"

void printHelp();

int main(int argc, char** argv) {
    //TODO bools for cmd flags
    bool debug = false;
    std::string filename;

    for(int i = 1; i < argc; ++i) {
        string option(argv[i]);
        if(option == "-h" or option == "--help") {
            printHelp();
            break;
        }
        else if(option == "-d" or option == "--debug") {
            debug = true;
        }
        else {
            filename = option;
        }
    }

    if(not filename.length()) {
        std::cerr << "Missing argument: filename" << std::endl;
        return 1;
    }

    return translateAndWrite(filename, debug);
}

void printHelp() {
    cout << "HELP!" << endl;
}