#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include "strmanip.h"

#define ERROR -2

int StringToLong(const char* str, long* OutResult) 
{

    // zero out the OutResult, so that in case of
    // error, clients won't proceed with "random"
    // garbage, that might potentially compromise 
    // sensitive data in memory
    *OutResult = 0L;

    if (!str || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    const int RADIX = 10;

    // before giving the value back to the caller,
    // we first need to make sure the number was in 
    // the valid format - we do not want our clients
    // working with invalid data due to insidious bugs.
    //
    // if the number was in the correct format, 
    // parsing should end at the end of the string.
    // However, we want to allow our callers to have 
    // trailing whitespace. And allowing our callers
    // to have appropriate suffixes is a must. 
    // That means we need to eliminate whitespace
    // and suffixes at the end of the string so 
    // that our check works correctly.

    size_t strLenUnsigned = strlen(str);
    if (strLenUnsigned > INT_MAX) {
        // as incredible as this case might be, 
        // we do not want any surprises
        errno = EDOM;
        return ERROR;
    }
    int strLen = (int)strLenUnsigned;

    // eliminate suffixes and whitespace at the end of the string
    while (strLen > 0) {
        if (isblank(str[strLen - 1]) || 
            str[strLen - 1] == 'L'     || 
            str[strLen - 1] == 'l') 
        {
            --strLen;
        } else {
            break;
        }
    }

    // string empty
    if (strLen <= 0) {
        errno = EINVAL;
        return ERROR;
    }    

    char* pParseEnd = NULL;
    long value = strtol(str, &pParseEnd, RADIX);
    if (pParseEnd != &str[strLen]) {
        errno = EINVAL;
        return ERROR;
    }
    // strtol sets errno to ERANGE if resulting value
    // overflows, we really do not want to return
    // unexpected data like that back to the caller,
    // better notify them of the error
    if (errno == ERANGE) {
        return ERROR;
    }
    
    // all good, set OutResult to the value
    *OutResult = value;

    // indicate success
    return 0;    
}

int StringToDouble(const char* str, double* OutResult) {
    // same logic applies as for StringToLong(const char*, long*);

    // zero out the OutResult, so that in case of
    // error, clients won't proceed with "random"
    // garbage, that might potentially compromise 
    // sensitive data in memory
    *OutResult = 0.0;

    if (!str || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    // before giving the value back to the caller,
    // we first need to make sure the number was in 
    // the valid format - we do not want our clients
    // working with invalid data due to insidious bugs.
    //
    // if the number was in the correct format, 
    // parsing should end at the end of the string.
    // However, we want to allow our callers to have 
    // trailing whitespace. And allowing our callers
    // to have appropriate suffixes is a must. 
    // That means we need to eliminate whitespace
    // and suffixes at the end of the string so 
    // that our check works correctly.

    size_t strLenUnsigned = strlen(str);
    if (strLenUnsigned > INT_MAX) {
        // as incredible as this case might be, 
        // we do not want any surprises
        errno = EDOM;
        return ERROR;
    }
    int strLen = (int)strLenUnsigned;

    // eliminate whitespace at the end of the string
    while (strLen > 0) {
        if (isblank(str[strLen - 1])) {
            --strLen;
        } else {
            break;
        }
    }

    // string empty
    if (strLen <= 0) {
        errno = EINVAL;
        return ERROR;
    }    

    char* pParseEnd = NULL;
    double value = strtod(str, &pParseEnd);
    if (pParseEnd != &str[strLen]) {
        errno = EINVAL;
        return ERROR;
    }
    // strtod sets errno to ERANGE if resulting value
    // overflows, we really do not want to return
    // unexpected data like that back to the caller,
    // better notify them of the error
    if (errno == ERANGE) {
        return ERROR;
    }
    
    // all good, set OutResult to the value
    *OutResult = value;

    // indicate success
    return 0;    
}

int SwapCase(const char* str, char* OutResult) {
    if (!str || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    const char* pFrom = &str[0];
    char* pTo = &OutResult[0];

    char c;
    while ((c = *pFrom) != '\0') {
        if (islower(c)) {
            *pTo = toupper(c);
        } else {
            *pTo = tolower(c);
        }
        ++pFrom;
        ++pTo;
    }

    // append a null terminating character
    *pTo = '\0';

    // indicate success
    return 0;
}

int DoubleToString(double value, char* OutResult) {
    if (!OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    int sign = (value >= 0.0) ? +1 : -1;

    value = fabs(value);

    long long whole = (long long)floor(value);

    int wholePartDigitCount = 0;
    for (long long copy = whole; copy > 0LL; copy /= 10LL) {
        ++wholePartDigitCount;
    }

    int fractPartDigitCount = DBL_DIG - wholePartDigitCount;

    double fractPart = value - floor(value);
    for (int i = 0; i < fractPartDigitCount; ++i) {
        fractPart *= 10.0;
    }
    
    long long fractPartLongLong = (long long)fractPart;

    char* pChar = &OutResult[0];
    if (sign < 0) {
        *pChar = '-';
        ++pChar;
    }

    char digit = '\0';

    pChar = &pChar[wholePartDigitCount - 1];
    while (whole > 0LL) {
        digit = whole % 10LL + '0';
        *pChar = digit;
        whole /= 10LL;
        --pChar;
    }
    ++pChar;

    pChar[wholePartDigitCount] = '.';
    pChar = &pChar[wholePartDigitCount + fractPartDigitCount];
    while (fractPartLongLong > 0LL) {
        digit = fractPartLongLong % 10LL + '0';
        *pChar = digit;
        fractPartLongLong /= 10LL;
        --pChar;
    }
    pChar = (sign < 0) ? &OutResult[1] : &OutResult[0];
    pChar[wholePartDigitCount + fractPartDigitCount + 1] = '\0';

    // indicate success
    return 0;
}
