/*
K.N.King "C Programming. A Modern Approach."
Programming project 9 p.177

Write a program that generates a "random walk" across 
a 10 x 10 array. The array will contain chracters (all
'.' initially). The program must randomly "walk" from
element to element, always going up, down, left, or right
by one element. The elements visited by the program will
be labeled with the letters A through Z, in the order
visited. Here's an example of the desired output:

A . . . . . . . . .
B C D . . . . . . .
. F E . . . . . . .
H G . . . . . . . .
I . . . . . . . . .
J . . . . . . . Z .
K . . R S T U V Y .
L M P Q . . . W X .
. N O . . . . . . .
. . . . . . . . . .

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ROW_COUNT    10
#define COL_COUNT    10
#define EMPTY_CELL    '.'

enum Direction {
    North,
    South,
    West,
    East
};
const int ENUM_DIRECTION_COUNT = 4;

int main(void)
{
    char world[ROW_COUNT][COL_COUNT] = { 
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
        { EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL, EMPTY_CELL },
    };
    
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);

    int row = 0;
    int col = 0;

    enum Direction dir = South;

    int isDirectionValid = 0;
    int arePathsExhausted = 0;
    
    for (char c = 'A'; c <= 'Z' && !arePathsExhausted; ++c) 
    {                
        world[row][col] = c;

        arePathsExhausted = 
                   world[row - 1][col] != EMPTY_CELL
                && world[row + 1][col] != EMPTY_CELL
                && world[row][col - 1] != EMPTY_CELL
                && world[row][col + 1] != EMPTY_CELL;

        if (!arePathsExhausted)
        {
            // reset isDirectionValid to false to trigger
            // the direction-finding loop
            isDirectionValid = 0;
        
            while (!isDirectionValid)
            {
                isDirectionValid = 1;
                        
                dir = (enum Direction)( rand() % ENUM_DIRECTION_COUNT);

                if (dir == North && row - 1 >= 0 && world[row - 1][col] == EMPTY_CELL) {
                    --row;
                } else if (dir == South && row + 1 < ROW_COUNT && world[row + 1][col] == EMPTY_CELL) {
                    ++row;
                } else if (dir == West && col - 1 >= 0 && world[row][col - 1] == EMPTY_CELL) {
                    --col;
                } else if (dir == East && col + 1 < COL_COUNT && world[row][col + 1] == EMPTY_CELL) {
                    ++col;
                } else {
                    isDirectionValid = 0;
                }
            }
        }
    }

    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COL_COUNT; ++j) {
            printf("%c ", world[i][j]);
        }
        putchar('\n');
    }

    getchar();
    return EXIT_SUCCESS;
}
