#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

/*
Empty vector used to initialize new stacks
*/
const std::vector<char> emptyVector;

int main() {
    std::ifstream input("input.txt");

    std::vector<std::vector<char>> stacks;

    while(!input.eof()) {
        std::string line;
        getline(input, line);

        // If the row is empty, skip it
        if(line.size() == 0) continue; 

        // If the row is just the stack numbers, skip it
        if(line.at(1) >= '1' && line.at(1) <= '9') { 
            continue;
        }

        // If the row is an instruction
        if(line.at(0) == 'm') {
            // Utilize a stringstream for the extraction operator
            std::stringstream ss(line);

            /*
            Params Array
            [0] Number of crates to move
            [1] Stack to take crates from
            [2] Stack to move crates to 
            */
            int params[3] = {0};

            // Read the instruction into the stringstream and extract the numbers from it
            while(!ss.eof()) {
                std::string paramStr;
                ss >> paramStr;
                int param = atoi(paramStr.c_str());

                //Check if the param is a number (it will be zero if it is just text)s
                if(param != 0) {
                    /*
                    Calculate the index of the next non-zero element in the params array,
                    and write the param to it.
                    */
                    params[(params[0] != 0) + (params[1] != 0)] = param;
                }
            }

            /*
            Decrement the written index of the stacks,
            since the stacks vector indexes from 0, not 1
            */
            params[1]--;
            params[2]--;

            /*
            Copy the bottom-most crate that must be moved from the source to the destination stack
            Then remove it from the original stack.

            Repeat until all crates have been moved
            */
            for(int i = 0; i < params[0]; i++) {
                int crateToRemove = stacks[params[1]].size() - params[0] + i;  
                char crate = stacks[params[1]].at(crateToRemove);
                stacks[params[2]].push_back(crate);
                stacks[params[1]].erase(stacks[params[1]].begin() + crateToRemove);
            }
        }
        // If the row is describing the initial stack configuration
        else {
            int stack = 0;
            for(int i = 1; i < line.size(); i += 4) {

                // Initialize an empty stack if it doesn't already exist
                if(stacks.size() <= stack) {
                    stacks.push_back(emptyVector);
                }

                // If there is a crate present, put it on the stack vector
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

    /*
    Print the topmost crate on each stack
    */
    for(int i = 0; i < stacks.size(); i++) {
        printf("%c", stacks[i].back());
    }
    
    printf("\n");

    return 0;
}