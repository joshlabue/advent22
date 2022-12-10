#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::ifstream input("input.txt");
    std::string instruction;

    /*
    List of values to sum.
    If 0, consider it a noop. It doesn't cause the register to change.
    Otherwise, the values will be added to the register one at a time.
    */
    std::vector<int> program;
    
    while(!input.eof()) {
        input >> instruction;

        /*
        If the instruction is addx,
        - Add an instruction that adds 0 to the register, effectively doing nothing
        - Add an instruction that adds the directed value

        This causes addx instructions to take two clock cycles to execute,
        since the first clock cycle adds zero, and the second carries out
        the operation.
        */
        if(instruction == "addx") {
            input >> instruction;
            program.push_back(0);
            program.push_back(atoi(instruction.c_str()));
        }
        else {
            program.push_back(0);
        }
        
    }

    int xRegister = 1;
    int strengthSum = 0;

    for(int i = 0; i < program.size(); i++) {
        int cycle = i + 1;

        /*
        If the cycle index follows the sequence 20 + 40n,
        record its signal strengh and add it to the sum of others.
        */
        if(cycle % 40 == 20) {
            strengthSum += xRegister * cycle;
        }

        xRegister += program[i];
    }

    printf("%d\n", strengthSum);
    return 0;
}