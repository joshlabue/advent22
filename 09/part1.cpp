#include <iostream>
#include <fstream>
#include <tuple>
#include <cmath>
#include <map>

/*
Number of knots in the rope.
*/
const int knots = 2;

struct Coordinate {
    int x = 0;
    int y = 0;
};

int main() {
    std::ifstream input("input.txt");

    /*
    List of knots.
    0 corresponds to the head,
    The last value corresponds to the tail.
    */
    Coordinate rope[knots];

    /*
    Map of all values that have been visited.
    */
    std::map<std::string, bool> visited;

    /*
    Explicitly declare that the origin has been visited by the tail
    */
    visited.insert({"0:0", true});

    while(!input.eof()) {
        std::string direction, steps;
        
        input >> direction;
        input >> steps;

        int stepCount = atoi(steps.c_str());

        for(int i = 0; i < stepCount; i++) {

            /*
            Detemine the direction the head should move based on the input
            */
            if(direction == "U") rope[0].y++;
            else if(direction == "D") rope[0].y--;
            else if(direction == "L") rope[0].x--;
            else if(direction == "R") rope[0].x++;

            /*
            Knot movement simulation.
            For each knot, move towards previous knot if necessary.
            */
            for(int knot = 1; knot < knots;  knot++) {
                int dx = (rope[knot-1].x - rope[knot].x);
                int dy = (rope[knot-1].y - rope[knot].y);
                
                /*
                If the two knots are adjecent or directly diagonal.
                Implements Pythagorean Theorem to solve for distance between the two points.
                
                If the distance is greater than the distance of 2 diagonally adjacent knots
                (sqrt(2), or approximated to 1.5 in this case), then move the knot towards the
                previous knot.
                */
                if(sqrt(dx*dx + dy*dy) > 1.5) {
                    if(dx > 0) rope[knot].x++;
                    else if(dx < 0) rope[knot].x--;

                    if(dy > 0) rope[knot].y++;
                    else if(dy < 0) rope[knot].y--;

                    /*
                    If the knot is the tail, record its position in the map.
                    */
                    if(knot == knots - 1) {
                        char keyChar[10];
                        sprintf(keyChar, "%d:%d", rope[knot].x, rope[knot].y);

                        visited.insert({std::string(keyChar), true});
                    }
                }
            }
        }
    }

    printf("%d\n", visited.size());

    return 0;
}