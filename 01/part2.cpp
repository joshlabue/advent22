#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 

int main() {
    std::ifstream input("input.txt");
    
    std::vector<int> totals;
    int total = 0;

    std::string line = "";

    std::getline(input, line);
    while(!input.eof()) {
        if(line == "") { // if end of section
            totals.push_back(total);
            total = 0;
        } else {
            total += atoi(line.c_str());
        }
        std::getline(input, line);
    }
    totals.push_back(total);

    std::sort(totals.begin(), totals.end());

    total = 0;
    for(int i = 0; i < 3; i++) {
        total += totals[totals.size() - 1 - i];
    }

    printf("%d\n", total);

    return 0;
}


