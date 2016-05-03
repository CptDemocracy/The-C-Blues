/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.50

Write a program that asks the user to enter the numbers
from 1 to 16 (in any order) and then displays the numbers
in a 4 by 4 arrangement, followed by the sums of the rows,
columns and diagonals:

"Enter the numbers from 1 to 16 in any order:
16 3 2 13 5 10 11 8 9 6 7 12 4 15 14 1

16  3  2 13
 5 10 11  8
 9  6  7 12
 4 15 14  1

 Row sums: 34 34 34 34
 Column sums: 34 34 34 34
 Diagonal sums: 34 34
"

*/

#include <stdlib.h>
#include <stdio.h>

#define NUM_COUNT            16
#define COL_COUNT            4
#define ROW_COUNT            (NUM_COUNT / COL_COUNT)
#define INVALID_INPUT_MSG    "Input invalid. Please try again"

int sumArray(int *nums, int length, int step);

int main(void) {

    // where are my VLAs, Visual Studio 2015, where?
    int nums[NUM_COUNT] = { 0 };

    int isInputValid = 0;
    int diagSum1 = 0;
    int diagSum2 = 0;
    int rowSum = 0;
    int colSum = 0;
    int col = 0;
    int row = 0;

    // collect input
    printf("Enter the numbers from 1 to %d in any order:\n", NUM_COUNT);
    while (!isInputValid)
    {
        int i = 0;
        while (i < NUM_COUNT) {
            if ( scanf("%d", &nums[i]) < 1) 
            {                
                // discard illegal input
                char c = '\0';
                while ((c = getchar()) != '\n' && c != EOF) {
                    continue;
                }
                isInputValid = 0;
                break;
            };
            isInputValid = 1;
            ++i;
        }
        if (!isInputValid) puts(INVALID_INPUT_MSG);
    }
    getchar();

    // output input
    int i = 0;
    while (i < NUM_COUNT) {
        if ((i > 0) && ((i % COL_COUNT) == 0)) {
            putchar('\n');
        }
        printf("%2d ", nums[i]);
        ++i;
    }    
    putchar('\n');

    // count row sums
    printf("Row sums: ");
    for (row = 0; row < ROW_COUNT; ++row) {
        rowSum = sumArray(&nums[row * COL_COUNT], COL_COUNT, 1);
        printf("%d ", rowSum);
    }
    putchar('\n');

    // count col sums
    printf("Column sums: ");
    for (col = 0; col < COL_COUNT; ++col) {
        colSum = sumArray(&nums[col], NUM_COUNT, COL_COUNT);
        printf("%d ", colSum);
    }
    putchar('\n');

    i = 0;
    row = 0;
    col = 0;
    while (i < NUM_COUNT) {        
        if (col == row) {
            diagSum1 += nums[i];
        }
        if (col + row == COL_COUNT - 1) {
            diagSum2 += nums[i];
        }
        col = (col + 1) % COL_COUNT;
        if (col == 0) {
            ++row;
        }
        ++i;
    }
    printf("Diagonal sums: %d %d\n", diagSum1, diagSum2);
    getchar();
    return EXIT_SUCCESS;
}

int sumArray(int *nums, int length, int step) {
    if (!nums || step < 1) return 0;
    int sum = 0;
    for (int i = 0; i < length; i += step) {
        sum += nums[i];
    }
    return sum;
}
