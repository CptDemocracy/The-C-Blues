/*
K.N.King "C Programming. A Modern Approach."
Programming project 2 p.96

Write a program that asks the user for a 24-hour time,
then displays the time in 12-hour form:

"Enter a 24-hour time: 21:11
Equivalent 12-hour time: 9:11 PM
"

Be careful not to display 12:00 as 0:00.
*/

#include <stdlib.h>
#include <stdio.h>

#define HOURS_PER_DAY       24
#define MINUTES_PER_HOUR    60
#define MIDDAY_HOUR         12

enum TimePeriod { AM, PM };

int main(void) 
{
    char c = '\0';
    int hours12h = 0;
    int hours24h = 0;
    int minutes = 0;
    enum TimePeriod timePeriod = AM;

    printf("Enter a 24-hour time: ");
    while ( scanf("%d : %d", &hours24h, &minutes) < 2
        || hours24h >= HOURS_PER_DAY
        || hours24h < 0
        || minutes >= MINUTES_PER_HOUR
        || minutes < 0)
    {
        puts("Input invalid. Please try again.");

        // discard the rest of invalid input
        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    // discard trailing the trailing new line character/the rest of whitespace
    while ( (c = getchar()) != '\n' && c != EOF) continue;
    
    // convert 24 hours to 12 hours
    hours12h = (hours24h != MIDDAY_HOUR) ? hours24h % MIDDAY_HOUR : MIDDAY_HOUR;

    // calculate what time period it is
    if (hours24h >= MIDDAY_HOUR) {
        timePeriod = PM;
    } else {
        timePeriod = AM;
    }
    // output the result
    printf("Equivalent 12-hour time: %d:%02d %s\n", 
        hours12h, 
        minutes, 
        timePeriod == AM ? "AM" : "PM");
    getchar();

    return EXIT_SUCCESS;
}
