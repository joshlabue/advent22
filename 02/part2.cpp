#include <iostream>
#include <fstream>

int main() {

    std::ifstream input("input.txt");

    int score = 0;

    while(!input.eof()) {
        char opp, you;
        int p1, p2;

        /*
        Normalize the inputs so they are both 0 to 2
        0: Rock
        1: Paper
        2: Scissors
        */
        input >> opp;
        input >> you;

        p1 = opp - 'A';

        int matchPoints = 0;

        /*
        Determine what the match outcome must be,
        then choose the play needed to get that outcome.
        */
        if(you == 'X') { // Must lose
            if(p1 > 0) p2 = p1 - 1;
            else p2 = 2;
        }
        else if(you == 'Y') { // Must draw
            p2 = p1;
            
            matchPoints += 3;
        }
        else { // Must win
            if(p1 < 2) p2 = p1 + 1;
            else p2 = 0;

            matchPoints += 6;
        }

        /*
        Add the score for the play,
        Rock gets 1,
        Paper gets 2,
        Scissors gets 3.

        Since these plays are in the correct order already,
        we can just add 1 to the number of the play to get this score.
        */
        matchPoints += p2 + 1;

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