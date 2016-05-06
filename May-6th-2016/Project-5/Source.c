/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.157

In the SCRABBLE Crossword Game, players form words using small
tiles, each containing a letter and a face value. The face value
varies from one letter to another, based on the letter's rarity.

Here are the face values: 
1: AEILNORSTU, 
2: DG, 
3: BCMP, 
4: FHVWY,
5: K, 
8: JX, 
10: QZ.

"Enter a word: pitfall
Scrabble value: 12
"

Your program should allow any mixture of lowercase and uppercase
letters in the word.
*/

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

int main(void) {

    const int lookupTable[UCHAR_MAX] = {
        ['A'] = 1, ['a'] = 1,
        ['E'] = 1, ['e'] = 1,
        ['I'] = 1, ['i'] = 1,
        ['L'] = 1, ['l'] = 1,
        ['N'] = 1, ['n'] = 1,
        ['O'] = 1, ['o'] = 1,
        ['R'] = 1, ['r'] = 1,
        ['S'] = 1, ['s'] = 1,
        ['T'] = 1, ['t'] = 1,
        ['U'] = 1, ['u'] = 1,

        ['D'] = 2, ['d'] = 2,
        ['G'] = 2, ['g'] = 2,

        ['B'] = 3, ['b'] = 3,
        ['C'] = 3, ['c'] = 3,
        ['M'] = 3, ['m'] = 3,
        ['P'] = 3, ['p'] = 3,

        ['F'] = 4, ['f'] = 4,
        ['H'] = 4, ['h'] = 4,
        ['V'] = 4, ['v'] = 4,
        ['W'] = 4, ['w'] = 4,
        ['Y'] = 4, ['y'] = 4,

        ['K'] = 5, ['k'] = 5,

        ['J'] = 8, ['j'] = 8,
        ['X'] = 8, ['x'] = 8,

        ['Q'] = 10, ['q'] = 10,
        ['Z'] = 10, ['z'] = 10,
    };
    
    char c = '\0';
    int score = 0;
    int count = 0;

    while (c != EOF)
    {
        score = 0;
        count = 0;

        while ((c = getchar()) != '\n' && c != EOF) {
            if (isalpha(c)) score += lookupTable[c];
            ++count;
        }
        if (count > 0) printf("Score: %d\n", score);
    }
    getchar();

    return EXIT_SUCCESS;
}
