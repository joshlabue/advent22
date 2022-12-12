#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*
Number of rounds to simulate
*/
const int roundCount = 10000;

enum Operation {
    ADD, MULTIPLY, SQUARE
};

struct Monkey {
    std::vector<long> items;
    Operation operation;
    int operand = 0;
    int test = 0;
    int testTrue = 0;
    int testFalse = 0;
};

int main() {
    std::ifstream input("input.txt");
    std::string line;

    std::vector<Monkey> monkeys;

    /*
    Parse the input data.
    Each cycle of this loop should catch an entire monkey entry.
    */
    while(!input.eof()) {
        Monkey monkey;

        getline(input, line); // monkey number
        getline(input, line); // starting items
        line = line.substr(18);
        
        
        char itemString[2];
        /*
        Parse the list of item values.
        They are all 2 characters long,
        so just look at every nth character and atoi it.
        */
        for(int i = 0; i <= line.size(); i++) {
            if(i % 4 == 0) itemString[0] = line.at(i);
            else if(i % 4 == 1) itemString[1] = line.at(i);
            else if(i % 4 == 2) {
                int itemValue = atoi(itemString);
                monkey.items.push_back(itemValue);
            }
        }

        getline(input, line); // operation
        line = line.substr(23);
        char operation = line.at(0);
        line = line.substr(2);
        if(line == "old") {
            monkey.operation = SQUARE;
        }
        else {
            if(operation == '+') monkey.operation = ADD;
            else if(operation == '*') monkey.operation = MULTIPLY;
            monkey.operand = atoi(line.c_str());
        }
        
        getline(input, line); // test condition
        line = line.substr(21);
        monkey.test = atoi(line.c_str());

        getline(input, line); // if true
        line = line.substr(29);
        monkey.testTrue = atoi(line.c_str());

        getline(input, line); // if false
        line = line.substr(30);
        monkey.testFalse = atoi(line.c_str());

        getline(input, line); // blank line, skip
        // printf("monkey created\n");
        
        monkeys.push_back(monkey);

    }

    int lcm = 1;
    bool lcmMatch = false;
    /*
    Calculate the least common multiple (lcm) of the monkeys' test divisors.
    This is needed to keep the worry levels from overflowing.

    Since we only need to know if it is divisible by values a/b/c, we can just find the
    lcm for a, b, and c and mod the worry value once it exceeds the lcm.
    */
    while(lcmMatch == false) {
        lcm++;

        bool possibleMatch = true;
        for(int i = 0; i < monkeys.size(); i++) {
            if(lcm % monkeys[i].test != 0) {
                possibleMatch = false;
                break;
            }
        }

        lcmMatch = possibleMatch;  
    }

    /*
    Run rounds of inspection/throws
    */
    std::vector<int> inspectionCount(monkeys.size());
    for(int round = 0; round < roundCount; round++) {
        for(int monkey = 0; monkey < monkeys.size(); monkey++) {
            for(int item = 0; item < monkeys[monkey].items.size(); item++) {
                inspectionCount[monkey]++;
                long itemWorry = monkeys[monkey].items[item];

                /*
                Perform whatever operation the monkey does on the item
                */
                if(monkeys[monkey].operation == ADD) itemWorry += monkeys[monkey].operand;
                else if(monkeys[monkey].operation == MULTIPLY) itemWorry *= monkeys[monkey].operand;
                else if(monkeys[monkey].operation == SQUARE) itemWorry *= itemWorry;


                int throwTo;
                /*
                Run the divisiblility test on the worry value.
                If it passes, throw it to the true monkey.
                It it fails, throw it to the false monkey.
                */                
                if(itemWorry % monkeys[monkey].test == 0) {
                    throwTo = monkeys[monkey].testTrue;
                }
                else {
                    throwTo = monkeys[monkey].testFalse;
                }

                /*
                Set item worry to itemworry mod lcm.
                The purpose is described above by the lcm calculation loop.
                */
                itemWorry %= lcm;

                monkeys[throwTo].items.push_back(itemWorry);
            }
            /*
            Delete the monkey's inventory, since it will have thrown all of its items to another monkey.
            */            
            monkeys[monkey].items.clear();
        }
    }
    
    /*
    Sort the inspection count
    */
    std::sort(inspectionCount.begin(), inspectionCount.end());

    long monkeyBusiness = 1;    
    /*
    Multiply the top two inspection counts for the monkey business value.
    */    
    for(int i = 1; i <= 2; i++) {
        monkeyBusiness *= inspectionCount[inspectionCount.size() - i];
    }    

    printf("%ld\n", monkeyBusiness);

    return 0;
}