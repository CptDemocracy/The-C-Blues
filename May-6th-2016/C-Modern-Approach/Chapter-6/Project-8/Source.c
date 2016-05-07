/*
K.N.King "C Programming. A Modern Approach."
Programming project 8 p.157

"Modify Programming project 8 from chapter 5 so that 
the user enters a time using the 12-hour clock. The 
input will have the form:

hours:minutes

followed by either A, P, AM, or PM (either lowercase or 
uppercase). Whitespace is allowed (but not required)
between the numerical time and the AM/PM indicator.
"
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define HOURS_PER_DAY           24
#define MINUTES_PER_HOUR        60
#define MIDDAY_HOUR             12
#define BUFFER_SIZE             256

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

int StringToUpper(char* s);

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
        8:00am                     10:16am
        9:43am                     11:52am
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
            .arrivalTime = { .hours = 3, .minutes = 0, .timePeriod = PM },
        }
    };    
    const size_t FLIGHT_COUNT = sizeof(flightSchedule) / sizeof(flightSchedule[0]);
    char buffer[BUFFER_SIZE] = { 0 };
    int hours = 0;
    int minutes = 0;
    enum TimePeriod userTimePeriod = AM;
    char c = '\0';
    char* pchar = NULL;

    printf("Please enter a 12-hour time: ");

    while (1)
    {
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            return EXIT_FAILURE;
        }
        if (buffer[strlen(buffer) - 1] != '\n') {

            // if users managed to pass more characters 
            // than BUFFER_SIZE allows - discard trailing input
            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        // no need to worry about writing past the buffer, since
        // we are extracting a substring which will obviously be
        // of length less than the size of the whole string in 
        // the buffer
        if ( sscanf(buffer, "%d : %d %s", &hours, &minutes, buffer) <3) {
            fprintf(stderr, "Input invalid. Please try again.\n");
            continue;
        }

        if ((hours >= HOURS_PER_DAY || hours < 0)
            || (minutes >= MINUTES_PER_HOUR || minutes < 0))
        {
            fprintf(stderr, "Input invalid. Please make sure the time is in a 24-hour format.\n");
            continue;
        }

        // validate the substring, should be either A, P, AM, or PM 
        // (either lowercase or uppercase)
        
        // no need to skip whitespace, sscanf has already done it for us

        // convert buffer to uppercase for case insensitive comparison
        StringToUpper(buffer);
        
        if ( strcmp(buffer, "AM") == 0 || strcmp(buffer, "A")) {
            userTimePeriod = AM;
            break;
        } else if ( strcmp(buffer, "PM") == 0 || strcmp(buffer, "P")) {
            userTimePeriod = PM;
            break;
        } else {
            fprintf(stderr, "Time period invalid. Time period should be either A, P, AM, or PM"
                            " (either lowercase or uppercase)\n");
            continue;
        }
    }
    struct ShortTimeStamp12Hour userTime12Hour = { 
        .hours = hours, 
        .minutes = minutes, 
        .timePeriod = userTimePeriod 
    };

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

    printf("Closest departure time: %02d:%02d %s\n",
        nearestDeparturePtr->departureTime.hours,
        nearestDeparturePtr->departureTime.minutes,
        nearestDeparturePtr->departureTime.timePeriod == AM ? "AM" : "PM");
    printf("Arriving at: %02d:%02d %s\n",
        nearestDeparturePtr->arrivalTime.hours,
        nearestDeparturePtr->arrivalTime.minutes,
        nearestDeparturePtr->arrivalTime.timePeriod == AM ? "AM" : "PM");

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
    if (!key 
        || !base 
        || count < 1 
        || elemSize < 1 
        || !cmp) 
    {
        return -1;
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

int StringToUpper(char* s) {
    if (!s) return 1;

    while (*s) {
        *s = toupper(*s);
        ++s;
    }
    
    return 0;
}
