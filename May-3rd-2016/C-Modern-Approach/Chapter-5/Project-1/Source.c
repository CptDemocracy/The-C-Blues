/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.96

Write a program that calculates how many digits
a number contains:

"Enter a number: 374
The number 374 has 3 digits
"

You may assume that the number has no more than four digits.

*/

#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    // since we may assume that the number has no more than
    // four digits, we are going to use simple integer math
    // to deduce the number of digits.

    // a genuine solution would involve simple char fetching
    // from the input stream, validating and counting the number
    // of characters fetched.

    int n = 0;
    char c = '\0';
    int digcount = 0;

    printf("Enter a number: ");
    while (scanf("%d", &n) < 1) 
    {
        puts("Input invalid. Please try again.");

        // discard the rest of invalid input
        while ((c = getchar()) != '\n' && c != EOF) continue;
    }
    // discard trailing whitespace characters
    while ((c = getchar()) != '\n' && c != EOF) continue;

    int ncopy = 0;

    if (n == INT_MIN) {
        // INT_MIN requires special treatment
        // since if n == INT_MIN, then n == -n
        ncopy = n;
        do {
            ++digcount;
            ncopy /= 10;
        } while (ncopy < 0);
    } else {
        ncopy = n > 0 ? n : -n;
        do {
            ++digcount;
            ncopy /= 10;
        } while (ncopy > 0);
    }
    printf("The number %d has %d digit%s", 
        n, 
        digcount, 
        digcount == 1 ? "" : "s");

    getchar();
    return EXIT_SUCCESS;
}
