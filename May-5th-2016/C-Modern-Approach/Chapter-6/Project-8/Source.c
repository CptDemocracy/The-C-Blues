/*
K.N.King "C Programming. A Modern Approach."
Programming project 8 p.121

Write a program that prints a one-month calendar. The user
specifies the number of days in the month and the day of the
week on which the month begins:

"Enter number of days in month: 31
Enter starting day of the week (1=Sun, 7=Sat): 3
       1  2  3  4  5
 6  7  8  9 10 11 12
13 14 15 16 17 18 19
20 21 22 23 24 25 26
27 28 29 30 31
"
*/

#include <stdlib.h>
#include <stdio.h>

enum DayOfWeek {
    Sunday,        
    Monday,        
    Tuesday,    
    Wednesday,    
    Thursday,    
    Friday,        
    Saturday,    
};

#define MAX_DAYS_IN_MONTH    31
#define MIN_DAYS_IN_MONTH    28

int main(void) 
{
    int daysInMonth = 0;
    enum DayOfWeek startingDay = Sunday;
    int scanfState = 0;
    char c = '\0';

    printf("Please enter the number of days in month: ");

    while (1)
    {
        scanfState = scanf("%d", &daysInMonth);

        if (scanfState != 1) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            while ( (c = getchar()) != '\n' && c != EOF) continue;
            continue;
        }
        // We don't really need to discard the trailing new 
        // line character at this point, since the consequent
        // scanf call will consume it properly. However, to 
        // ensure flexibility, we leave it here.
        while ( (c = getchar()) != '\n' && c != EOF) continue;

        if (daysInMonth < MIN_DAYS_IN_MONTH || daysInMonth > MAX_DAYS_IN_MONTH) {
            fprintf(
                stderr, 
                "Input invalid. The smallest number of days possible is"
                "%d days and the largest number of days is %d\n", 
                MIN_DAYS_IN_MONTH, 
                MAX_DAYS_IN_MONTH);
            continue;
        }

        break;
    }

    printf("Please enter the starting day of the week. (1=Sun, 7=Sat): ");
    while (1)
    {
        scanfState = scanf("%d", &startingDay);
        if (scanfState != 1) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            while ( (c = getchar()) != '\n' && c != EOF) continue;
            continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;
        
        // decrement to comply with DayOfWeek mapping
        --startingDay;

        if (startingDay < Sunday || startingDay > Saturday) {
            fprintf(
                stderr, 
                "Invalid value for the starting day. Please make "
                "sure it is within the range of %d to %d inclusive.\n",
                Sunday, Saturday);
            continue;
        }

        break;
    }        
    
    enum DayOfWeek currentDay = Sunday;

    while (currentDay < startingDay) {
        printf("%2s ", "");
        currentDay = (currentDay + 1) % Saturday;
    }
    for (int day = 1; day <= daysInMonth; ++day) {
        printf("%2d ", day);

        currentDay = (currentDay + 1) % Saturday;
        if (currentDay == Sunday) {
            putchar('\n');
        }
    }
    getchar();

    return EXIT_SUCCESS;
}
