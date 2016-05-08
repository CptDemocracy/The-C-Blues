/*
K.N.King "C Programming. A Modern Approach."
Programming project 2 p.177

Modify the repdigit.c program of Section 8.1
so that it prints a table showing how many
times each digit appears in the number:

"Enter a number: 41271092
Digit:          0 1 2 3 4 5 6 7 8 9
Occurences:     1 2 2 0 1 0 0 1 0 1

*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    int lookupTable[UCHAR_MAX] = { 0 };
    char c = '\0';
    int isInputValid = 0;

    printf("Please enter a number: ");
    while (!isInputValid)
    {
        // reset all values in the table to zero
        memset(lookupTable, 0, UCHAR_MAX * sizeof(char));

        // let's assume for a moment input is valid
        isInputValid = 1;

        while ( (c = getchar()) != '\n' && c != EOF) {
            if (!isdigit(c)) {
                // do not break out here, we still
                // need to discard invalid input
                isInputValid = 0;
            } else {
                lookupTable[c] += 1;
            }
        }
        if (!isInputValid) {
            fprintf(stderr, "Input invalid. Please try again.\n");
        }
    }
    
    printf("%-12s", "Digit:");
    for (unsigned int i = '0'; i <= '9'; ++i) {
        printf("%2c ", i);
    }
    putchar('\n');

    printf("%-12s", "Occurences:");
    for (unsigned int i = '0'; i <= '9'; ++i) {
        printf("%2d ", lookupTable[i]);
    }
    putchar('\n');

    getchar();
    return EXIT_SUCCESS;
}
