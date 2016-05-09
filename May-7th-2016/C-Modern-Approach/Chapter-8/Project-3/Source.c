/*
K.N.King "C Programming. A Modern Approach."
Programming project 3 p.177

Modify the repdigit.c program of Section 8.1
so that the user can enter more than one number
to be tested for repeated digits. The program
should terminate when the user enters a number
that's less than or equal to 0.

*/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

int main(void)
{
    char hashTable[UCHAR_MAX] = { 0 };
    char c = '\0';
    int isInputValid = 0;
    int count = 0;

    while (1)
    {
        isInputValid = 0;        

        printf("Please enter a number (or 0 to terminate the program): ");
        while (!isInputValid)
        {
            isInputValid = 1;
            count = 0;
            memset(hashTable, 0, UCHAR_MAX * sizeof(char));
            
            while ( (c = getchar()) != '\n' && c != EOF) {            
                if (!isdigit(c)) {
                    // can't break out on the spot since we still
                    // need to discard user input
                    isInputValid = 0;
                } else {
                    hashTable[c] += 1;
                    ++count;
                }
            }
            if (!isInputValid) {
                fprintf(stderr, "Not a valid number. Please try again.\n");
            }
        }

        if (count == 1 && hashTable['0'] == 1) {
            break;
        }

        printf("Repeated digits: ");

        for (unsigned int i = 0; i < UCHAR_MAX; ++i) {
            if (hashTable[i] > 1) {
                printf("%c ", i);
            }
        }
        putchar('\n');
    }    

    getchar();
    return EXIT_SUCCESS;
}
