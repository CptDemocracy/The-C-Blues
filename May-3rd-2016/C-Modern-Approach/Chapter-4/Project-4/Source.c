/*
K.N.King "C Programming. A Modern Approach."
Programming project 4 p.71

Write a program that reads an integer entered by 
the user and displays it in octal (base 8):

"Enter a number between 0 and 32767: 1953
In octal, your number is: 03641
"

The output should be displayed using five digits,
even if fewer digits are sufficient.

*/

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    const int LOWER_BOUND = 0;
    const int UPPER_BOUND = (int)SHRT_MAX;

    int n = 0;
    char c = '\0';
    printf("Please enter a number between %d and %d: ", LOWER_BOUND, UPPER_BOUND);
    while (scanf("%d", &n) < 1 || n < LOWER_BOUND || n >= UPPER_BOUND) {
        puts("Input invalid. Please try again.");

        // consume trailing invalid input
        while ((c = getchar()) != '\n' && c != EOF) continue;
    }
    // consume trailing chars
    while ((c = getchar()) != '\n' && c != EOF) continue;
    printf("In octal, your number is: %05o\n", n);    
    getchar();
    return EXIT_SUCCESS;
}
