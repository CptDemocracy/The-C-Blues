/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.121

Write a program that finds the largest in a series
of numbers entered by the user. The program must
prompt the user to enter numbers one by one. When
the user enters 0 or a negative number, the program
must display the largest nonnegative number entered:

"Enter a number: 60
Enter a number: 38.3
Enter a number: 4.89
Enter a number: 100.65
Enter a number: 75.2295
Enter a number: 0

The largest number entered was 100.62."

*/

#include <stdlib.h>
#include <float.h>
#include <stdio.h>

// Returns a boolean specifying whether user has 
// entered a value that signifies whether he's 
// done entering the input.
int ShouldTerminate(double number);

int main(void) 
{
    double number = 0.0;
    double max = DBL_MIN;
    int count = 0;

    char c = '\0';

    while (1) 
    {
        printf("Enter a number: ");
        while (scanf("%lf", &number) != 1) {
            puts("Input invalid. Please try entering this number again.");

            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;

        printf("Number %g accepted.\n", number);
        putchar('\n');

        if (ShouldTerminate(number)) {
            break;
        }
        max = (number > max) ? number : max;
        ++count;        
    }

    if (count < 1) {
        // We don't really need to use count to see if user
        // entered any input, a simple check against DBL_MIN
        // would do, since DBL_MIN is negative.
        //
        // However, that would introduce a few potential
        // problems. For one, should we change ShouldTerminate
        // to include negative numbers, DBL_MIN will be within
        // valid range and might introduce bugs in the program.
        // Yeah, I know, DBL_MIN is pretty much impossible to
        // "just" enter, however, as a good practice, we choose
        // to stay clear off of valid input ranges.
        //
        // The second problem would be the comparison. We would
        // need to define an EPSILON value to compare doubles, 
        // that would require us to use machine-dependent values
        // from float.h and make us worry about variouys floating 
        // point quirks and shenanigans.
        puts("No numbers were entered.");
    } else {
        printf("The largest number entered was: %g", max);
    }

    getchar();
    return EXIT_SUCCESS;
}

int ShouldTerminate(double number) {
    if (number <= 0.0) {
        return 1;
    }
    return 0;
}
