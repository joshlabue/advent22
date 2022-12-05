#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    std::ifstream input("input.txt");

    std::vector<std::vector<char>> stacks;
    std::vector<char> emptyVector;
    stacks.push_back(emptyVector);

    while(!input.eof()) {
        std::string line;
        getline(input, line);

        if(line.size() == 0) continue;
        if(line.at(1) >= '1' && line.at(1) <= '9') {
            continue;
        }

        if(line.at(0) == 'm') {

            std::stringstream ss(line);

            int params[3] = {0};
            while(!ss.eof()) {
                std::string paramStr;
                ss >> paramStr;
                int param = atoi(paramStr.c_str());
                if(param != 0) {
                    params[(params[0] != 0) + (params[1] != 0)] = param;
                }
            }
            // printf("move %d crates from stack %d to stack %d\n", params[0], params[1], params[2]);

            for(int i = 0; i < params[0]; i++) {
                int crateToRemove = stacks[params[1]].size() - params[0] + i;  
                char crate = stacks[params[1]].at(crateToRemove);
                stacks[params[2]].push_back(crate);
                stacks[params[1]].erase(stacks[params[1]].begin() + crateToRemove);
            }
        }
        else {

            int stack = 1;
            for(int i = 1; i < line.size(); i += 4) {

                // If the stack list is too small, initialize a new stack
                if(stacks.size() <= stack) {
                    stacks.push_back(emptyVector);
                }

                if(line.at(i) != ' ') {
                    std::string character;
                    character = line.at(i);
                    stacks[stack].insert(stacks[stack].begin(), line.at(i));
                }
                
                stack++;
            }
        }


        input.peek();
    }

    for(int i = 1; i < stacks.size(); i++) {
        printf("%c", stacks[i].back());
    }
    
    printf("\n");

    return 0;
}