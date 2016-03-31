#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-8. There is no error checking in day_of_year or month_day. Remedy this defect.
*/

static const char daytab[2][13] = {
 {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
 {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day);

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {    

    int day  = 31;
    int mon  = 3;
    int year = 2016;

    int dayOfYear = 0;

    dayOfYear = day_of_year(year, mon, day);
    printf("%02d/%02d/%d, day of year: %d\n", day, mon, year, dayOfYear);

    ++dayOfYear;

    month_day(year, dayOfYear, &mon, &day);
    printf("%02d/%02d/%d, day of year: %d\n", day, mon, year, dayOfYear);

    getchar();
    return 0;
}

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    if (year <= 0 || month < 1 || month > 12 || day <= 0) {
        errno = EINVAL;
        return -1;
    }
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if (day > daytab[leap][month]) {
        errno = EINVAL;
        return -1;
    }
    for (i = 1; i < month; i++)
        day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    if (year <= 0 || yearday <= 0 || !pmonth || !pday) {
        errno = EINVAL;
        return;
    }
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    if ((leap && yearday > 366) ||
        (!leap && yearday > 365)) 
    {
        errno = EINVAL;
        return;
    }
    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}
