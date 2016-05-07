/*
K.N.King "C Programming. A Modern Approach."
Programming project 9 p.157

Write a program that asks the user for a 12-hour time,
then displays the time in 24-hour form:

hours:minutes

followed by either A, P, AM, or PM (either lowercase or 
uppercase). Whitespace is allowed (but not required)
between the numerical time and the AM/PM indicator.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE         256
#define MINUTES_PER_HOUR    60
#define MIDDAY_HOUR         12

enum TimePeriod { AM, PM };

struct ShortTimeStamp24Hour
{
    int hours;
    int minutes;
};

struct ShortTimeStamp12Hour
{
    int hours;
    int minutes;
    enum TimePeriod timePeriod;
};

struct ShortTimeStamp24Hour* ShortTimeStamp12HourConvertToShortTimeStamp24Hour(
    const struct ShortTimeStamp12Hour* stamp, 
    struct ShortTimeStamp24Hour* OutResult);

int main(void) {

    char buffer[BUFFER_SIZE] = { 0 };
    int hours = 0;
    int minutes = 0;
    char c = '\0';
    char* pchar = NULL;
    struct ShortTimeStamp12Hour userTime12Hour = { 0 };
    struct ShortTimeStamp24Hour userTime24Hour = { 0 };

    while (1)
    {
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            return EXIT_FAILURE;
        }
        // if user enters input longer than BUFFER_SIZE - 1,
        // discard the trailing input
        // we can detect that if the last character before
        // the null terminating character is not equal to a
        // new line feed
        if (buffer[strlen(buffer) - 1] != '\n') {
            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        // consume the numbers, store the rest of input back
        // in the buffer
        if ( sscanf(buffer, "%d : %d %s", &hours, &minutes, buffer) <3
            || (hours < 0 || hours > MIDDAY_HOUR)
            || (minutes < 0 || minutes >= MINUTES_PER_HOUR)) 
        {
            fprintf(stderr, "Input invalid. Please try again.\n");
            continue;
        }
        
        pchar = buffer;

        // convert to upper case for case insensitive comparison
        while ((c = *pchar) != '\0') {
            *pchar = toupper(c);
            ++pchar;
        }

        if (strcmp(buffer, "AM") == 0 || strcmp(buffer, "A") == 0) {
            userTime12Hour.timePeriod = AM;
            break;
        } else if (strcmp(buffer, "PM") == 0 || strcmp(buffer, "P") == 0) {
            userTime12Hour.timePeriod = PM;
            break;
        }
        continue;
    }
    userTime12Hour.hours = hours;
    userTime12Hour.minutes = minutes;

    ShortTimeStamp12HourConvertToShortTimeStamp24Hour(&userTime12Hour, &userTime24Hour);

    printf("%d:%d\n", userTime24Hour.hours, userTime24Hour.minutes);
    getchar();

    return EXIT_SUCCESS;
}

struct ShortTimeStamp24Hour* ShortTimeStamp12HourConvertToShortTimeStamp24Hour(
    const struct ShortTimeStamp12Hour* stamp, 
    struct ShortTimeStamp24Hour* OutResult)
{
    if (!stamp || !OutResult) return NULL;
    
    OutResult->hours = 
        (stamp->timePeriod == PM && stamp->hours != MIDDAY_HOUR) ? stamp->hours + MIDDAY_HOUR : stamp->hours;
    OutResult->minutes = stamp->minutes;

    return OutResult;
}
