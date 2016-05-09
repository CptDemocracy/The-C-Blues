/*
K.N.King "C Programming. A Modern Approach."
Programming project 7 p.177

"Enter row 1: 8 3 9 0 10
Enter row 2: 3 5 17 1 1
Enter row 3: 2 8 6 23 1
Enter row 4: 15 7 3 2 9
Enter row 5: 6 14 2 6 0

Row totals: 30 27 40 36 28
Column totals: 34 37 37 32 21
"
*/

#include <stdlib.h>
#include <stdio.h>

#define ROW_COUNT 5
#define COL_COUNT 5

int main(void)
{
    int matrix[ROW_COUNT][COL_COUNT] = { 0 };
    char c = '\0';
    int j = 0;
    int sum = 0;

    for (int i = 0; i < ROW_COUNT; ++i) {        
        printf("Please enter row %d: ", i + 1);

        j = 0;
        while (j < ROW_COUNT)
        {
            if (scanf(" %d", &matrix[i][j]) != 1) {
                // if illegal, discard the whole line of input
                // and prompt for input again
                fprintf(stderr, "Input invalid. Please enter the row %d again.\n", i + 1);

                // discard invalid input
                while ( (c = getchar()) != '\n' && c != EOF) continue;

                j = 0;
                continue;
            }
            ++j;

            // check if end of the line
            c = getchar();
            if (c == '\n') {
                break;
            } else {
                if (j == ROW_COUNT) {
                    fprintf(stderr, "More than %d numbers in a row. Please make sure your row "
                                    "has only %d numbers and enter the row %d again.\n", ROW_COUNT, ROW_COUNT, i + 1);

                    // discard excessive input
                    while ( (c = getchar()) != '\n' && c != EOF) continue;

                    j = 0;
                    continue;
                }
                ungetc(c, stdin);
            }
        }
    }

    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COL_COUNT; ++j) {
            printf("%d ", matrix[i][j]);
        }
        putchar('\n');
    }

    printf("Row totals: ");
    for (int i = 0; i < ROW_COUNT; ++i) {
        sum = 0;
        for (int j = 0; j < COL_COUNT; ++j) {
            sum += matrix[i][j];
        }
        printf("%d ", sum);
    }
    putchar('\n');

    printf("Column total: ");
    for (int i = 0; i < COL_COUNT; ++i) {
        sum = 0;
        for (int j = 0; j < ROW_COUNT; ++j) {
            sum += matrix[j][i];
        }
        printf("%d ", sum);
    }
    putchar('\n');
    getchar();
    return EXIT_SUCCESS;
}
