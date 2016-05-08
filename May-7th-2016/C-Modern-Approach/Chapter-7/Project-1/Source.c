/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.177
Modify the repdigit.c program of Section 8.1 so that
it shows which digits (if any) were repeated:
"Enter a number: 939577
Repeated digits: 7 9
"
*/

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    char hashTable[UCHAR_MAX] = { 0 };
    char c = '\0';
    int isInputValid = 0;

    printf("Please enter a number: ");

    while (!isInputValid)
    {
        isInputValid = 1;
        while ( (c = getchar()) != '\n' && c != EOF) {            
            if (!isdigit(c)) {
                // can't break out on the spot since we still
                // need to discard user input
                isInputValid = 0;
            } else {
                hashTable[c] += 1;
            }
        }
        if (!isInputValid) {
            fprintf(stderr, "Not a valid number. Please try again.\n");
        }
    }

    printf("Repeated digits: ");

    for (unsigned int i = 0; i < UCHAR_MAX; ++i) {
        if (hashTable[i] > 1) {
            printf("%c ", i);
        }
    }
    putchar('\n');

    getchar();
    return EXIT_SUCCESS;
}
