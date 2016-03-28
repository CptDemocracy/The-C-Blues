/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
 (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
 through 9, a through f, and A through F.
*/

#include <stdio.h>
#include <errno.h>
#include <ctype.h>

int htoi(const char* hex) {
    
    if (!hex) {
        errno = EINVAL;
        return 0;
    }

    int num  = 0;
    int sign = 1;
    const char* pbegin = &hex[0];

    // skip whitespace    
    while (isspace(*pbegin)) ++pbegin;

    if (*pbegin != 'x' && *pbegin != 'X' && *pbegin != '0' && *pbegin != '-') {
        errno = EINVAL;
        return 0;
    }

    if (*pbegin == '-') {
        sign = -sign;
        ++pbegin;
    }
    else if (*pbegin == 'x' || *pbegin == 'X') {
        ++pbegin;
    }
    else if (*pbegin == '0') {
        ++pbegin;
        if (*pbegin != 'x' && *pbegin != 'X') {
            errno = EINVAL;
            return 0;
        }
        ++pbegin;
    }

    // locate the end of the literal and  
    // validate characters at the same time
    const char* pend = pbegin;
    while (*pend && !isblank(*pend)) {
        if (!isxdigit(*pend)) {
            errno = EINVAL;
            return 0;
        }
        ++pend;
    }

    // parse the value
    const char* pchar = pend - 1;

    size_t bitpos = 0;
    while (pchar >= pbegin) {
        int digit = *pchar - '0';

        // if overflown
        if (num + digit * (1 << (4 * bitpos)) < num) {            
            errno = ERANGE;
            return 0;
        }

        num += digit * (1 << (4 * bitpos));
        ++bitpos;
        --pchar;
    }

    // iterate until the end of the string
    // if found anything but blanks, throw 
    // error
    while (*pend) {
        if (!isspace(*pend)) {
            errno = EINVAL;
            return num;
        }
        ++pend;
    }

    return num;
}

int main(void)
{
    printf("%d\n", htoi("0x80"));
    printf("%d\n", htoi("x80"));
    printf("%d\n", htoi("80"));

    getchar();
    return 0;
}
