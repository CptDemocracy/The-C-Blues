/*
K.N.King "C Programming. A Modern Approach."
Programming project 17 p.177

Write a program that prints an n x n magic square
(a square arrangement of the numbers 1, 2, ..., n^2)
in which the sums of the rows, columns, and diagonals
are all the same). The user will specify the value of n:

"This program creates a magic square of a specified size.
The size must be an odd number between 1 and 99:
Enter size of magic square: 5
17 24  1  8 15
23  5  7 14 16
 4  6 13 20 22
10 12 19 21  3
11 18 25  2  9
"

Store the magic square in a two-dimensional array. Start by
placing the number 1 in the middle of row 0. Place each of
the remaining numbers 2, 3, ..., n^2 by moving up one row
and over one column. Any attempt to go outside the bounds
of the array should "wrap around" to the opposite side of
the array. For example, instead of storing the next number
in column n, we would store it in column 0. If a particular
array element is already occupied, put the number directly
below the previously stored number. If your compiler supports
variable-length arrays, declare the array to have n rows and
n columns. If not, declare the array to have 99 rows and 99
columns.
*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{    
    int n = 0;
    char c = '\0';

    printf(    "This program creates a magic square of a specified size.\n"
            "The size must be an odd number between 1 and 99.\n");
    while (1)
    {
        printf("Please enter a size of magic square: ");
        while ( scanf(" %d", &n) != 1) {
            fprintf(stderr, "Input invalid. Please make sure you are entering an odd integer number.\n");

            while ((c = getchar()) != '\n' && c != EOF) continue;
        }
        while ((c = getchar()) != '\n' && c != EOF) continue;

        if (n % 2 == 0) {
            fprintf(stderr, "Input invalid. The size of a magic square must be an odd number.\n");
        } else {
            break;
        }
    }

    int count = n * n;
    int* magic = (int*)calloc(count, sizeof(int));
    if (!magic) {
        return EXIT_FAILURE;
    }
    int row = 0;
    int col = n / 2;

    int nextRow = 0;
    int nextCol = 0;

    for (int i = 0; i < count; ++i) 
    {        
        magic[row * n + col] = i + 1;

        nextRow = (row - 1) < 0 ? n - 1 : row - 1;
        nextCol = (col + 1) % n;

        if (magic[nextRow * n + nextCol] != 0) {
            row = (row + 1) % n;
        } else {
            row = nextRow;
            col = nextCol;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%2d ", magic[i * n + j]);
        }
        putchar('\n');
    }
    free(magic);

    getchar();
    return EXIT_SUCCESS;
}
