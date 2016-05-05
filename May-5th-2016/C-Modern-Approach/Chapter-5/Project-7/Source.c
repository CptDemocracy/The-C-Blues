/*
K.N.King "C Programming. A Modern Approach."
Programming project 7 p.96

Write a program that finds the largest and
smallest of four integers entered by the user:

"Enter four integers: 21 43 10 35
Largest: 43
Smallest: 10
"

Use as few if statements as possible.
*/

/*
I actually added extra requirements to the problem to make it more challenging.
Unlike the problem, that requires only 4 digits to be read, my challenge is to
allow users to enter as many values as possible, separated by whitespace, and 
terminate the array of values by a sending a new line character to the stream.
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(void) 
{
    const char SEPARATOR = ' ';

    char c = '\0';
    int number = 0;
    int max = INT_MIN;
    int min = INT_MAX;
    
    printf("Please enter an array of integers separated by a \"%c\":\n", SEPARATOR);
    while (1) {
        if ( scanf("%d", &number) != 1) {
            puts("Input invalid. Please try again.");

            // make sure we reset the min and max values
            // on error, else they will persist
            max = INT_MIN;
            min = INT_MAX;

            // discard the rest of invalid input
            while ( (c = getchar()) != '\n' && c != EOF) continue;
        } else {
            if (number > max) max = number;
            if (number < min) min = number;
            // check the stream for the new line character,
            // if it's there, that means user has submitted input
            while ( (c = getchar()) && c != '\n' && c == SEPARATOR) continue;
            if (c == '\n') {
                break;
            } else {
                // we've consumed the character that is not
                // whitespace, so put it back in the stream
                ungetc(c, stdin);
            }
        }
    }
    printf("Largest: %d\n", max);
    printf("Smallest: %d\n", min);
    getchar();

    return EXIT_SUCCESS;
}
