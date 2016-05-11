/*
K.N.King "C Programming. A Modern Approach."
Programming project 18 p.311

Write a program that accepts a date from the user in the form
mm/dd/yyyy and then displays it in the form "month dd, yyyy,"
where month is the name of the month:

"Enter a date (mm/dd/yyyy): 2/17/2011
You entered the date February 17, 2011"

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_DAYS_IN_MONTH 31

int main(const int argc, const char* argv[]) {

    const static char* MONTH_NAMES[] = {
        [0] = NULL, // a placeholder for simplifying program logic
        [1] = "January",
        [2] = "February",
        [3] = "March",
        [4] = "April",
        [5] = "May",
        [6] = "June",
        [7] = "July",
        [8] = "August",
        [9] = "September",
        [10] = "October",
        [11] = "November",
        [12] = "December"
    };
    const static int MONTH_COUNT 
        = (int)(sizeof(MONTH_NAMES) / sizeof(MONTH_NAMES[0]));

    int day = 0;
    int month = 0;
    int year = 0;

    char c = '\0';

    printf("Please enter a date (mm/dd/yyyy): ");
    while ( scanf("%d / %d / %d", &month, &day, &year) <3 
        || month < 1 || month > MONTH_COUNT
        || day < 0 || day > MAX_DAYS_IN_MONTH) 
    {
        fprintf(stderr, "Input invalid. Please try again.\n");

        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    const char* monthString = NULL;
    monthString = MONTH_NAMES[month];

    printf("You entered the date %s %d, %d%s.", monthString, day, abs(year), year < 0 ? " B.C" : "");

    getchar();
    return EXIT_SUCCESS;
}
