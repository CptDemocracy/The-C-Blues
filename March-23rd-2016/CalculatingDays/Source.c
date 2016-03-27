#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include "Utilities.h"

#define DEFAULT_SHORT_DATE_STRING_COUNT 32
#define DEFAULT_SHORT_DATE_STRING_FORMAT "%d/%m/%y"

int main(void) {

    struct tm dateinfo1 = { 
        0, .tm_mday = 2,  .tm_mon = JUL, .tm_year = 2005 
    };
    struct tm dateinfo2 = { 
        0, .tm_mday = 16, .tm_mon = JUL, .tm_year = 2005 
    };

    int days = CalculateDaysBetween(&dateinfo1, &dateinfo2);

#ifdef DEBUG
    // CalculateDaysBetween(const struct tm*, const struct tm*) 
    // sets errno to EINVAL if passed dates earlier than March 1900
    if (errno == EINVAL) {
        perror(NULL);
    }
#endif

    // zero out for safety
    char dateinfo1_cstr[DEFAULT_SHORT_DATE_STRING_COUNT] = { 0 };

    // strftime's _SizeInBytes argument already provides for the null-
    // terminating character
    strftime(dateinfo1_cstr, 
        DEFAULT_SHORT_DATE_STRING_COUNT, 
        DEFAULT_SHORT_DATE_STRING_FORMAT, 
        &dateinfo1);
    
    // zero out for safety
    char dateinfo2_cstr[DEFAULT_SHORT_DATE_STRING_COUNT] = { 0 };

    // stftime's _SizeInBytes argument already provides for the null-
    // termianting character
    strftime(dateinfo2_cstr,
        DEFAULT_SHORT_DATE_STRING_COUNT,
        DEFAULT_SHORT_DATE_STRING_FORMAT,
        &dateinfo2);

    printf("%d days have passed between %s and %s.\n", 
        days, dateinfo1_cstr, dateinfo2_cstr);

    getchar();
    
    return 0;
}
