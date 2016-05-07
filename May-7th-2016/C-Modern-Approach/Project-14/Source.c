/*
K.N.King "C Programming. A Modern Approach."
Programming project 14 p.157

Write a program that uses Newton's method to compute the square
root of a positive floating-point number:

"Enter a positive number: 3
Square root: 1.73205
"

*/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

double NewtonSquareRoot(double num);

int main(void)
{    
    double num = 0.0;
    double sqrRoot = 0.0;

    char c = '\0';

    int isNumberValid = 0;

    printf("Please enter a positive number: ");
    while (!isNumberValid) 
    {
        // assume the number is valid
        isNumberValid = 1;
        
        if ( scanf(" %lf", &num) != 1) {
            isNumberValid = 0;
            fprintf(stderr, "Input invalid. Please try again.\n");
        }
        if (num < 0.0) {
            isNumberValid = 0;
            fprintf(stderr, "Number cannot be negative. Please try again.\n");
        }
        // discard irrelevant trailing input
        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    sqrRoot = NewtonSquareRoot(num);
    printf("Square root: %g\n", sqrRoot);

    getchar();
    return EXIT_SUCCESS;
}

double NewtonSquareRoot(double num) {
    if (num < 0) {
        errno = EDOM;
        return 0.0;
    }
    const double EPSILON = 1.0 * pow(10.0, -1.0 * (DBL_DIG - 1));

    double guess = num / 2.0;
    while ( fabs(guess * guess - num) > EPSILON) {
        guess = (guess + num / guess) / 2.0;
    }
    return guess;
}
