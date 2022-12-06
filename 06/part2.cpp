#include <iostream>
#include <fstream>
#include <string>

/*
Length of start-of-packet marker
*/
const int markerLength = 14;

int main() {
    std::ifstream input("input.txt");
    std::string signal;

    input >> signal;

    for(int i = markerLength - 1; i < signal.length(); i++) {
        /*
        Stores a vector of bits, each bit representing a different letter.
        */
        uint32_t uniqueCharVector = 0;

        /*
        Step through the input string with a window matching the marker size
        */
        for(int j = markerLength - 1; j >= 0; j--) {
            
            /*
            A good bit of stuff to break down here (ba dum tss).

            First, convert a letter to its alphabetical index.
            a -> 0
            ...
            z -> 25

            Then, bit shift 1 to the left so that it resides at that index.
            Bitwise OR that with the existing vector, resulting in a value with a 1 bit for each unique character.
            */
            uniqueCharVector |= (1 << (signal.at(i - j) - 'z' + 25));
        }

        int numHighBits = 0;
        /*
        Count the number of 1 bits in the bit vector
        */
        for(int bit = 0; bit < 32; bit++) {
            if(uniqueCharVector >> bit & 1) numHighBits++;
        }

        /*
        If each character is unique, print the index out.
        */
        if(numHighBits == markerLength) {
            printf("%d\n", i + 1);
            break;
        }
    }
    return 0;
}