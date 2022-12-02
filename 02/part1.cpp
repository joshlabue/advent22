#include <iostream>
#include <fstream>

int main() {
  
    std::ifstream input("input.txt");

    int score = 0;

    while(!input.eof()) {
        char opp, you;
        int p1, p2;

        input >> opp;
        input >> you;

        /*
        Normalize the inputs so they are both 0 to 2
        0: Rock
        1: Paper
        2: Scissors
        */
        p1 = opp - 'A';
        p2 = you - 'X';

        /*
        Detemine outcome of the match.
        Due to the circular nature of the game, the conditions are not wildly simple.
        */
        int outcome = p2 - p1;

        /*
        Add the score for the play,
        Rock gets 1,
        Paper gets 2,
        Scissors gets 3.

        Since these plays are in the correct order already,
        we can just add 1 to the number of the play to get this score.
        */
        int matchPoints = p2 + 1;

        if(outcome == -1 || outcome == 2) { // loss
            matchPoints += 0;
        }
        if(outcome == 1 || outcome == -2) { // win
            matchPoints += 6;
        }
        if(outcome == 0) { // draw
            matchPoints += 3;
        } 

        score += matchPoints;

        /*
        Peek at the input file.
        This allows the eof condition to update without doing a second pass on the last line.
        */
        input.peek();
    }

    printf("%d\n", score);

    return 0;
}