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

/*
Get character value of a priority.
Priorities 1-26 are lowercase a-z
Priorities 27-52 are uppercase A-Z
*/
char reversePriority(int priority) {
    if(priority <= 26) {
        return 'a' + priority - 1;
    }
    else {
        return 'A' + priority - 27;
    }
}

int main() {
    std::ifstream input("input.txt");
    std::vector<std::string> lines;

    int sum = 0;

    // Read lines out of file before solving
    while(!input.eof()) {
        std::string line;
        getline(input, line);

        lines.push_back(line);
    }

    /*
    Group inventory: Keeps track of which types of items exist in the groups of 3.
    */
    int groupInventory[53] = {0};

    for(int l = 0; l < lines.size(); l++) {

        /*
        If this is the first member of the group, clear the inventory.
        */
        if(l % 3 == 0) {
            for(int i = 0; i < 53; i++) groupInventory[i] = 0;
        }

        std::string line = lines[l];
        
        /*
        Individual member's inventory 
        At each index,
            false means the item is not in the member's bag
            true means the item is in the member's bag
        */
        bool inventory[53] = {false};

        for(int i = 0; i < line.length(); i++) {
            char compartmentAatI = line.at(i);
            int aIndex = priority(compartmentAatI);
            inventory[aIndex] = true;
        }

        /*
        Record the presence of each type of item in the group inventory.
        
        If any item's value in the group inventory is 3, it means that all
        three group members had at least one of the item, making that
        item the group's badge type.

        Add the priority of the badge to the sum.
        */
        for(int i = 0; i < 53; i++) {
            groupInventory[i] += inventory[i];

            if(groupInventory[i] == 3) {
                sum += i;
                break;
            }
        }

    }

    printf("%d\n", sum);

    return 0;
}
