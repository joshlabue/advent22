#include <iostream>
#include <fstream>
#include <vector>

/*
Get numeric priority of an item.
Lowercase a-z have priorities 1-26
Uppercase A-Z have priorities 27-52
*/
int priority(char item) {
    if(item >= 'a' && item <= 'z') {
        return item - 'z' + 26;
    }
    else {
        return item - 'Z' + 52;
    }
}

int main() {
    std::ifstream input("input.txt");
    std::vector<std::string> lines;

    int sum = 0;

    /*
    Read the lines into a vector before solving
    */
    while(!input.eof()) {
        std::string line;
        getline(input, line);

        lines.push_back(line);
    }

    for(int l = 0; l < lines.size(); l++) {
        /*
        Split the line in half, for the two compartments in the bag
        */
        std::string lineA = lines[l].substr(0,lines[l].length()/2);
        std::string lineB = lines[l].substr(lines[l].length()/2);

        /*
        Item Cache
        Keeps track of which letters are in each bag.
        Useful because it allows for very fast checks if an item exists in the bag.
        */
        int cache[53] = {0};

        // Take inventory of each item in the first compartment
        for(int i = 0; i < lineA.length(); i++) {
            char compartmentAatI = lineA.at(i);
            int aIndex = priority(compartmentAatI);
            cache[aIndex]++;
        }

        // Then, step through the second compartment until a common item is found.
        for(int i = 0; i < lineA.length(); i++) {
            char compartmentBatI = lineB.at(i);
            int bIndex = priority(compartmentBatI);
            if(cache[bIndex] > 0) {
                sum += bIndex;
                break;
            }
        }

    }

    printf("%d\n", sum);

    return 0;
}