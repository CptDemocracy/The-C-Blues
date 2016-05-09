/*
K.N.King "C Programming. A Modern Approach."
Programming project 15 p.157

Write a program that computes the factorial of
a positive integer:

"Enter a positive integer: 6
Factorial of 6: 720
"

*/

#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

long double CalculateFactorial(long double num);

int main(void)
{
    long double number = 0.0L;
    long double fact = 0.0L;
    int scanfState = 0;
    char c = '\0';
    int isNumberValid = 0;

    // notice %Lf (long double) as opposed to %lf (double)
    puts("Please enter a positive number to calculate its factorial: ");
    
    while (!isNumberValid)
    {
        // assume the number is valid
        isNumberValid = 1;

        if ( scanf(" %Lf", &number) != 1) {
            isNumberValid = 0;
        }
        if (number < 0.0L) {
            isNumberValid = 0;            
        }
        // see if users left any trailing input other than
        // whitespace, if they did, input is to be considered invalid
        // discard irrelevant trailing input
        while ( (c = getchar()) != '\n' && c != EOF) {
            if (!isspace(c)) {
                // do not break out on the spot, we still need
                // to discard the irrelevant input
                isNumberValid = 0;
            }            
        }
        if (!isNumberValid) {
            if (number < 0.0) {
                fprintf(stderr, "Cannot calculate a factorial of a negative number."
                                " Please try again.\n");
            } else {
                fprintf(stderr, "Input invalid. Please try again.\n");
            }
        }
    }
    fact = CalculateFactorial(number);
    printf("Factorial of %g: %g\n", number, fact);
    getchar();
    return EXIT_SUCCESS;
}

long double CalculateFactorial(long double num) {
    if (num < 0.0L) {
        errno = EDOM;
        return 0.0;
    }
    if (num <= 1.0L) {
        return 1.0L;
    }
    return num * CalculateFactorial(num - 1.0L);
}
