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

int IsLeapYear(int year);

enum Month {
    January     = 1,
    February    = 2,
    March       = 3,
    April       = 4,
    May         = 5,
    June        = 6,
    July        = 7,
    August      = 8,
    September   = 9,
    October     = 10,
    November    = 11,
    December    = 12
};

int main(const int argc, const char* argv[]) {

    const static char* MONTH_NAMES[] = {
        [0] = NULL, // a placeholder for simplifying program logic
        [January]    = "January",
        [February]   = "February",
        [March]      = "March",
        [April]      = "April",
        [May]        = "May",
        [June]       = "June",
        [July]       = "July",
        [August]     = "August",
        [September]  = "September",
        [October]    = "October",
        [November]   = "November",
        [December]   = "December"
    };
    const static int MONTH_COUNT 
        = (int)(sizeof(MONTH_NAMES) / sizeof(MONTH_NAMES[0]));

    const static int DAYS_PER_MONTH[] = {
        0, // a placeholder for simplifying program logic
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31
    };

    int day = 0;
    int month = 0;
    int year = 0;
    int isLeap = 0;

    char c = '\0';
    int scanfState = 0;
    int isValid = 0;

    printf("Please enter a date (mm/dd/yyyy): ");

    while (!isValid)
    {
        isValid = 1;
        scanfState = scanf("%d / %d / %d", &month, &day, &year);

        while ( (c = getchar()) != '\n' && c != EOF) continue;

        if (scanfState <3) {
            fprintf(stderr, "Input is invalid format. Please try again.\n");
            isValid = 0;
        }
        else if (month < 1 || month > MONTH_COUNT) {
            fprintf(stderr, "Invalid value for the month. Month must be greater"
                            " or equal to one and less or equal to %d\n", 
                            MONTH_COUNT);
            isValid = 0;
        }
        else if (day < 0) {
            fprintf(stderr, "Invalid value for the day. Day cannot be a negative value.\n");
            isValid = 0;
        }
        else if ((day > DAYS_PER_MONTH[month]) 
            || ((isLeap = IsLeapYear(day)) && month == February && day > DAYS_PER_MONTH[month] + 1))
        {
            fprintf(stderr, "Invalid value for the day. Day cannot be greater than %d.\n", 
                isLeap ? DAYS_PER_MONTH[month] + 1 : DAYS_PER_MONTH[month]);
            isValid = 0;
        }
    }

    const char* monthString = NULL;
    monthString = MONTH_NAMES[month];

    printf("You entered the date %s %d, %d%s.", monthString, day, abs(year), year < 0 ? " B.C" : "");

    getchar();
    return EXIT_SUCCESS;
}

int IsLeapYear(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}
