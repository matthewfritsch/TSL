#include <iostream>
#include <vector>

struct option {
    std::string optionName;
    bool enabled;
};

int main(int argc, char** argv) {
    std::vector<option> options = parseArgs(argc, argv);
    

    return 0;
}

std::vector<option> parseArgs(int argc, char** argv) {
    std::vector<option> options;



    return options;
}