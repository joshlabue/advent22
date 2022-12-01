#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");
    
    int bestTotal = 0;
    int total = 0;
    std::string line = "";
    
    std::getline(input, line);
    while(!input.eof()) {
        if(line == "") { // if end of section
            if(total > bestTotal) {
                bestTotal = total;
            }
            total = 0;
        } else {
            total += atoi(line.c_str());
        }
        
        std::getline(input, line);
    }

    printf("%d\n", bestTotal);
    return 0;
}


