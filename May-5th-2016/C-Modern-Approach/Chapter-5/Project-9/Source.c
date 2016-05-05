/*
K.N.King "C Programming. A Modern Approach."
Programming project 9 p.96

Write a program that prompts the user to enter two dates
and then indicates which date comes earlier on the calendar:

"Enter first date (mm/dd/yy): 3/6/08
Enter second date (mm/dd/yy): 5/17/07
5/17/07 is earlier than 3/6/08
"
*/

#include <stdlib.h>
#include <stdio.h>

enum Month {
    January = 1, 
    February = 2, 
    March = 3,
    April = 4, 
    May = 5, 
    June = 6,
    July = 7,
    August = 8, 
    September = 9, 
    October = 10,
    November = 11, 
    December = 12
};

static const NON_LEAP_DAYS_PER_MONTH[] = {
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

struct ShortDate 
{
    int month;
    int day;
    int year;
};

int IsLeapYear(int year);

int ShortDateValidate(const struct ShortDate* date);

int ShortDateCompare(
    const struct ShortDate* date1, 
    const struct ShortDate* date2);

int main(void) 
{
    char c = '\0';
    int comp = 0;

    struct ShortDate 
        date1 = { 0 },
        date2 = { 0 },        
        *later = NULL,
        *earlier = NULL;

    printf("Enter first date (mm/dd/yy): ");
    while ( scanf("%02d / %02d / %02d", &date1.month, &date1.day, &date1.year) <3
        || !ShortDateValidate(&date1) ) 
    {
        puts("Input is in invalid format. Please try again.");

        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    printf("Enter second date (mm/dd/yy): ");
    while ( scanf("%02d / %02d / %02d", &date2.month, &date2.day, &date2.year) <3
        || !ShortDateValidate(&date2) ) 
    {
        puts("Input is in invalid format. Please try again.");

        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    comp = ShortDateCompare(&date1, &date2);

    if (comp == 0) {
        puts("Both dates are equal.");
    } else {
        if (comp > 0) {
            earlier = &date2;
            later = &date1;
        } else {
            earlier = &date1;
            later = &date2;
        }
    }
    printf("%02d/%02d/%02d is earlier than %02d/%02d/%02d\n",
        earlier->month,
        earlier->day,
        earlier->year,
        later->month,
        later->day,
        later->year
    );
    getchar();
    return EXIT_SUCCESS;
}

int IsLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); 
}

int ShortDateValidate(const struct ShortDate* date) {
    if (!date) return 0;
    
    enum Month month = (enum Month)date->month;
    int day = date->day;

    if (month < January || month > December) {
        return 0;
    }

    if (day < 1) return 0;

    if (month == February 
        && IsLeapYear(date->year)) 
    {
        if (day > NON_LEAP_DAYS_PER_MONTH[month - 1] + 1) {
            return 0;
        }
        return 1;
    } 
    else if (day > NON_LEAP_DAYS_PER_MONTH[month - 1]) {
        return 0;
    }

    return 1;
}

int ShortDateCompare(
    const struct ShortDate* date1, 
    const struct ShortDate* date2) 
{
    if (!date1 && !date2) return 0;
    if (!date1) return -1;
    if (!date2) return 1;
    
    if (date1->year < date2->year) return -1;
    if (date1->year > date2->year) return 1;

    if (date1->month < date2->month) return -1;
    if (date1->month > date2->month) return 1;

    if (date1->day < date2->day) return -1;
    if (date1->day > date2->day) return 1;

    return 0;
}
