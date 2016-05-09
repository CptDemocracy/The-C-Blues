/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.217

Write a function that computes the value of the following
polynomial:

3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6

Write a program that asks the user to enter a value for x,
calls the function to compute the value of the polynomial,
and then displays the value returned by the function.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

long double Fn(long double x);

int main(void)
{
    double x = 0.0;
    double result = 0.0;

    char c = '\0';

    printf(    "This program will calculate the value of: "
            "3x^5 + 2x^4 - 5x^3 - x^2 + 7x - 6\n");

    printf("Please enter the value of x: ");
    
    while (scanf("%Lf", &x) != 1) {
        fprintf(stderr, "Input invalid. Please try again.\n");

        while ((c = getchar()) != '\n' && c != EOF) continue;
    }
    while ((c = getchar()) != '\n' && c != EOF) continue;

    result = Fn(x);

    printf("= %g\n", result);

    getchar();
    return EXIT_SUCCESS;
}

long double Fn(long double x) {
    return 3 * powl(x, 5.0L) 
         + 2 * powl(x, 4.0L) 
         - 5 * powl(x, 3.0L)
         - powl(x, 2.0L) + 7 * x - 6;
}
