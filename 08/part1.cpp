#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

typedef std::vector<std::vector<int>> Map;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

/*
Generate a list of tree heights between a tree and a given edge
*/
std::vector<int> cardinalList(Map* map, int row, int col, Direction direction) {
    std::vector<int> list;
    
    bool reachedEdge = false;

    while(!reachedEdge) {
        switch(direction) {
            case UP:
                row--;
                break;
            case DOWN:
                row++;
                break;
            case LEFT:
                col--;
                break;
            case RIGHT:
                col++;
                break;
        }

        if(row < 0 || row == map->size() ||
            col < 0 || col == map->at(0).size()) {
                reachedEdge == true;
                break;
            }
        else {
            list.push_back(map->at(row).at(col));
        }
    }

    return list;
}

/*
Find whether a tree is visible.
AKA, Is the tree taller than all other trees in any cardinal direction?
*/
bool isVisible(Map* map, int row, int col) {
    int height = map->at(row).at(col);

    /*
    If the tree is on the border of the grid, it must be visible
    */
    if(row == 0 || row == map->size() - 1) return true;
    if(col == 0 || col == map->at(0).size() - 1) return true;

    /*
    For each cardinal direction, determine if the tree is taller than each one
    between itself and the edge of the map.

    Future optimization: don't bother checking every tree in each direction.
        Just get the height of the tallest tree and compare to that.
    */
    for(int dir = 0; dir <= 3; dir++) {
        bool lineOfSight = true;

        std::vector<int> pathToEdge;
        pathToEdge = cardinalList(map, row, col, (Direction)dir);


        for(int step = 0; step < pathToEdge.size(); step++) {
            if(pathToEdge.at(step) >= height) {
                lineOfSight = false;
                break;
            } 
        }

        if(lineOfSight) return true;        
    }
        
    return false;
}

int main() {
    std::ifstream input("input.txt");
    Map map;
    
    std::string line;

    /*
    Parse the input
    */
    while(!input.eof()) {
        input >> line;
        std::vector<int> row;
        for(int i = 0; i < line.size(); i++) {

            // Convert the digit char to an actual int
            row.push_back(line[i] - '0');
        }

        map.push_back(row);
    }

    int output = 0;

    /*
    Determine the visibility of each tree on the map
    */
    for(int row = 0; row < map.size(); row++) {
        for(int col = 0; col < map.at(0).size(); col++) {
            bool visible = isVisible(&map, row, col);
            output += visible;
        }
    }

    printf("%d\n", output);

    return 0;
}