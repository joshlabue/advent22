#include <iostream>
#include <fstream>

int main() {
    std::ifstream input("input.txt");

    int output = 0;

    while(!input.eof()) {
        std::string line;
        getline(input, line);

        std::string aStr, bStr;
        
        /*
        Split the string into two substrings, one for each pair
        Then, split the pair's substrings into their start and end positions
        */
        int comma = line.find(',');
        std::string pair[2];

        pair[0] = line.substr(0, comma);
        pair[1] = line.substr(comma + 1);

        int start[2], end[2];
        for(int i = 0; i < 2; i++) {
            int hyphen = pair[i].find('-');
            start[i] = stoi(pair[i].substr(0, hyphen));
            end[i] = stoi(pair[i].substr(hyphen + 1));
        }

        /*
        Check if the first set contains the second set.
        If not, check if the second contains the first.
        */
        for(int i = 0; i <= 1; i++) {
            bool containsOther = (start[i] <= start[!i]) && (end[i] >= end[!i]);
            if(containsOther) {
                output++;
                break;
            }
        }

        input.peek();
    }

    printf("%d\n", output);

    return 0;
}