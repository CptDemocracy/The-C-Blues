/*
K.N.King "C Programming. A Modern Approach."
Programming project 8 p.96

The following table shows the daily flights
from one city to another:

Departure time:         Arrival time:
8:00am                  10:16am
9:43am                  11:52am
11:19am                 1:31pm
12:47pm                 3:00pm

Write a program that asks user to enter a time
(expressed in hours and minutes, using the 24-
hour clock). The program then displays the 
departure and arrival times for the flight whose
departure time is closest to that entered by the 
user:

"Enter a 24-hour time: 13:15
Closest departure time is 12:47 p.m., arriving at 3:00 p.m.
"

*/

#include <stdlib.h>
#include <stdio.h>

#define HOURS_PER_DAY         24
#define MINUTES_PER_HOUR      60
#define MIDDAY_HOUR           12

/*
    Similar to the bsearch function, except
    that it returns an index to where the key
    is stored within array, or where it should 
    otherwise be inserted in case if it's not 
    present in the array.
*/
int BinarySearch(const void* key, 
    const void* base, 
    size_t count, 
    size_t elemSize, 
    int (*cmp)(const void*, const void*));

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

struct ShortTimeStamp12Hour* ShortTimeStamp24HourConvertToShortTimeStamp12Hour(
    const struct ShortTimeStamp24Hour* stamp, 
    struct ShortTimeStamp12Hour* OutResult);


int ShortTimeStamp12HourCompare(const struct ShortTimeStamp12Hour* stamp1, 
    const struct ShortTimeStamp12Hour* stamp2);

struct FlightTime 
{
    struct ShortTimeStamp12Hour departureTime;
    struct ShortTimeStamp12Hour arrivalTime;
};

int FlightTimeCompareByDepartureTime(const struct FlightTime* flight1,
    const struct FlightTime* flight2);

int main(void) {

    /*    
        Departure time:         Arrival time:
        8:00am                  10:16am
        9:43am                  11:52am
        11:19am                 1:31pm
        12:47am                 3:00pm
    */
    static const struct FlightTime flightSchedule[] = { 
        {
            .departureTime = { .hours = 8, .minutes = 0, .timePeriod = AM },
            .arrivalTime = { .hours = 10, .minutes = 16, .timePeriod = AM },
        },
        {
            .departureTime = { .hours = 9, .minutes = 43, .timePeriod = AM },
            .arrivalTime = { .hours = 11, .minutes = 52, .timePeriod = AM },
        },
        {
            .departureTime = { .hours = 11, .minutes = 19, .timePeriod = AM },
            .arrivalTime = { .hours = 1, .minutes = 31, .timePeriod = PM },
        },
        {
            .departureTime = { .hours = 12, .minutes = 47, .timePeriod = PM },
            .arrivalTime = { .hours = 3, .minutes = 3, .timePeriod = PM },
        }
    };    
    const size_t FLIGHT_COUNT = sizeof(flightSchedule) / sizeof(flightSchedule[0]);

    printf("Please enter a 24-hour time: ");

    int hours = 0;
    int minutes = 0;

    char c = '\0';
    while (scanf("%d : %d", &hours, &minutes) != 2
        || (hours >= HOURS_PER_DAY || hours < 0)
        || (minutes >= MINUTES_PER_HOUR || minutes < 0)) 
    {
        puts ("Input invalid. Please make sure the time is in a 24-hour format.");

        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    struct ShortTimeStamp24Hour userTime24Hour = { .hours = hours, .minutes = minutes };

    struct ShortTimeStamp12Hour userTime12Hour = { 0 };
    ShortTimeStamp24HourConvertToShortTimeStamp12Hour(&userTime24Hour, &userTime12Hour);

    // we are going to use the fact that the  flight times are sorted
    int nearestDepartureIndex = BinarySearch(
        &userTime12Hour, 
        flightSchedule, 
        FLIGHT_COUNT, 
        sizeof(flightSchedule[0]), 
        FlightTimeCompareByDepartureTime
    );
    if (nearestDepartureIndex < 0) {
        return EXIT_FAILURE;
    }
    const struct FlightTime* nearestDeparturePtr = &flightSchedule[nearestDepartureIndex];

    printf("Nearest departure: %02d:%02d %s",
        nearestDeparturePtr->departureTime.hours,
        nearestDeparturePtr->departureTime.minutes,
        nearestDeparturePtr->departureTime.timePeriod == AM ? "AM" : "PM");

    getchar();
    return EXIT_SUCCESS;
}

int ShortTimeStamp12HourCompare(const struct ShortTimeStamp12Hour* stamp1, 
    const struct ShortTimeStamp12Hour* stamp2)
{
    if (!stamp1 && !stamp2) return 0;
    if (!stamp1) return -1;
    if (!stamp2) return 1;
    if (stamp1->timePeriod != stamp2->timePeriod) {
        if (stamp1->timePeriod == AM) return -1;
        if (stamp1->timePeriod == PM) return 1;
    }
    return (MINUTES_PER_HOUR * stamp1->hours + stamp1->minutes) 
         - (MINUTES_PER_HOUR * stamp2->hours + stamp2->minutes);
}

int FlightTimeCompareByDepartureTime(const struct FlightTime* flight1,
    const struct FlightTime* flight2)
{
    if (!flight1 && !flight2) return 0;
    if (!flight1) return -1;
    if (!flight2) return 1;
    return ShortTimeStamp12HourCompare( &(flight1->departureTime), &(flight2->departureTime));
}

int BinarySearch(const void* key, 
    const void* base, 
    size_t count, 
    size_t elemSize, 
    int (*cmp)(const void*, const void*))
{
    const static int ERROR = -1;

    if (!key 
        || !base 
        || count < 1 
        || elemSize < 1 
        || !cmp) 
    {
        return ERROR;
    }

    int lo = 0;
    int hi = count;
    int mp = (lo + hi) / 2;

    int comp = 0;

    while (lo <= hi) {
        comp = (*cmp)(key, (char*)base + mp * elemSize);
        if (comp > 0) {
            lo = mp + 1;
        } else if (comp < 0) {
            hi = mp - 1;
        } else {
            return mp;
        }
        mp = (lo + hi) / 2;
    }
    return hi == count ? hi : hi + 1;
}

struct ShortTimeStamp12Hour* ShortTimeStamp24HourConvertToShortTimeStamp12Hour(
    const struct ShortTimeStamp24Hour* stamp, 
    struct ShortTimeStamp12Hour* OutResult)
{
    if (!stamp || !OutResult) return NULL;
        
    OutResult->timePeriod = (stamp->hours >= MIDDAY_HOUR) ? PM : AM;
    OutResult->hours = (stamp->hours != MIDDAY_HOUR) ? stamp->hours % MIDDAY_HOUR : MIDDAY_HOUR;
    OutResult->minutes = stamp->minutes;

    return OutResult;
}
