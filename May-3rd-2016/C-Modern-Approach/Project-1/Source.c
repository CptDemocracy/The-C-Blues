/*
K.N.King "C Programming. A Modern Approach."

Programming project 1 p.50

"Write a program that accepts a date from the user in the form
mm/dd/yyyy and then displays it in the form yyyymmdd:

Enter a date (mm/dd/yyyy): 2/17/2011
You entered the date 20110217
"

*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int month = 0;
    int year = 0;
    int day = 0;
    
    printf("Please enter a date (mm/dd/yyyy): ");

    // loop until input is valid
    // mm/dd/yyyy format
    while (scanf("%d/%d/%d", &month, &day, &year) < 3) 
    {
        // scanf failed, input invalid
        puts(    "Uh-oh. Input invalid. Did you include "
                "the slashes between the numbers?");

        // consume the rest of illegal input
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF) {
            // technically speaking, we can never reach
            // EOF on stdin, however, if getchar will 
            // somehow fail, it return EOF
            continue;
        }
    }
    // consume the trailing new-line character
    getchar();

    // yyyymmdd format
    printf("You entered the date %d%02d%02d", year, month, day);
    getchar();

    return 0;
}
