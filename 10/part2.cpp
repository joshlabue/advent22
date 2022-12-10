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
    std::string line(40, ' ');

    for(int i = 0; i < program.size(); i++) {
        int pixel = i % 40;

        /*
        If the pixel's current position is over the sprite, light the pixel up.

        The sprite is 3 pixels wide, and is centered over the position equal
        to the value of the X register.
        */
        if(pixel >= xRegister - 1 && pixel <= xRegister + 1) {
            line[pixel] = '#';
        }

        int cycle = i + 1;

        /*
        Every 40 cycles, print the current line,
        and reset the line string to an empty one.
        */
        if(cycle % 40 == 0) {
            printf("%s\n", line.c_str());
            line = std::string(40, ' ');
        }

        xRegister += program[i];
    }

    return 0;
}