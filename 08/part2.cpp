#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

typedef std::vector<std::vector<int>> Map;

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

/*
Calculate the number of trees visible between the given tree
and the next one of equal or greater height in a given direction
*/
int viewDistance(Map* map, int row, int col, Direction direction) {
    int height = map->at(row).at(col);
    
    int dist = 1;
    bool blocked = false;

    while(!blocked) {
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

        if(row <= 0 || row >= map->size()-1 ||
            col <= 0 || col >= map->at(0).size()-1) {
                blocked = true;
                break;
        }
        else if(map->at(row).at(col) >= height) {
            blocked == true;
            break;
        }

        dist++;
        
    }

    return dist;
}

/*
Calculate the Scenic Score of a tree.
Scenic Score = Product of view distance in all 4 directions.
*/
int calculateScore(Map* map, int row, int col) {
    int score = 1;

    for(int dir = 0; dir <= 3; dir++) {
        int dist = viewDistance(map, row, col, (Direction)dir);
        score *= dist;
    }
        
    return score;
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
            int score = calculateScore(&map, row, col);
            if(score > output) output = score;
        }
    }

    printf("%d\n", output);

    return 0;
}