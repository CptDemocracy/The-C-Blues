/*
K.N.King "C Programming. A Modern Approach."
Programming project 4 p.157

Write a program that translates an alphabetic phone number into numeric form:

"Enter phone number: CALLATT
2255288

Enter phone number: 1-800-COL-LECT
1-800-265-5328
"
*/

#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

int main(void) {

    const int lookupTable[UCHAR_MAX] = {
        ['A'] = 2, ['a'] = 2,
        ['B'] = 2, ['b'] = 2,
        ['C'] = 2, ['c'] = 2,
        ['D'] = 3, ['d'] = 3,
        ['E'] = 3, ['e'] = 3,
        ['F'] = 3, ['f'] = 3,
        ['G'] = 4, ['g'] = 4,
        ['H'] = 4, ['h'] = 4,
        ['I'] = 4, ['i'] = 4,
        ['J'] = 5, ['j'] = 5,
        ['K'] = 5, ['k'] = 5,
        ['L'] = 5, ['l'] = 5,
        ['M'] = 6, ['m'] = 6,
        ['N'] = 6, ['n'] = 6,
        ['O'] = 6, ['o'] = 6,
        ['P'] = 7, ['p'] = 7,
        ['Q'] = 7, ['q'] = 7,
        ['R'] = 7, ['r'] = 7,
        ['S'] = 7, ['s'] = 7,
        ['T'] = 8, ['t'] = 8,
        ['U'] = 8, ['u'] = 8,
        ['V'] = 8, ['v'] = 8,
        ['W'] = 9, ['w'] = 9,
        ['X'] = 9, ['x'] = 9,
        ['Y'] = 9, ['y'] = 9,
        ['Z'] = 9, ['z'] = 9,
    };
    
    char c = '\0';
    
    printf("Please enter a phone number: ");
    while (c != EOF)
    {
        while ((c = getchar()) != '\n' && c != EOF) {
            if (isalpha(c)) {
                printf("%d", lookupTable[c]);
            } else {
                putchar(c);
            }
        }
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
