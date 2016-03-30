#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 3-5. Write the function itob(n,s,b) that converts the 
 integer n into a base b character representation in the string s. 
 In particular, itob(n,s,16) formats s as a hexadecimal integer in s. 

 */

#define BUFFER_SIZE    64

int Reverse(char* str);

int Itob(int n, char* str, size_t bufferLen, int base);

int main(void) {

    int n = CHAR_MIN;
    int base = 16;
    char buffer[BUFFER_SIZE] = { 0 };
    while (1) {
        Itob(n, buffer, BUFFER_SIZE, base);
        printf("%s\n", buffer);
        if (n == CHAR_MAX) {
            break;
        }
        ++n;
    }

    getchar();

    return 0;
}

int Reverse(char* str) {
    if (!str) {
        errno = EINVAL;
        return EINVAL;
    }
    char temp = 0;
    size_t len = strlen(str);
    for (size_t i = 0, j = len - 1; i < j; ++i, --j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
    return 0;
}

int Itob(int n, char* str, size_t bufferLen, int base) {

    if (!str || bufferLen < 1) {
        errno = EINVAL;
        return EINVAL;
    }
    if (base < 2 || base > 16) {
        errno = ERANGE;
        return ERANGE;
    }

    static const char BASE_CHARS[] = "0123456789ABCDEF";

    size_t i = 0;
    
    // in order to support the largest negative number
    // in a two's complement representation, we cannot
    // just invert negative numbers, since the largest 
    // negative number will simply remain negative due
    // to overwrapping. For this reason we set up two
    // conditional branches for negative and positive
    // values respectively. We could avoid branching
    // and cram everything into one loop, however, the
    // problem is, in my opinion, it affects readability 
    // for the worse

    int sign = n;
    
    int digit = 0;
    if (sign >= 0) {
        do {
            if (!(i < bufferLen - 1)) {
                break;
            }
            digit = n % base;
            str[i] = BASE_CHARS[digit];
            ++i;
            n /= base;
        } while (n > 0);
    } else {
        do {
            if (!(i < bufferLen -1)) {
                break;
            }
            digit = -(n % base);
            str[i] = BASE_CHARS[digit];
            ++i;
            n /= base;
        } while (n < 0);
    }

    if (!(i < bufferLen - 1)) {
        str[bufferLen - 1] = '\0';
        errno = EINVAL;
        return EINVAL;
    }

    // prepend a prefix if hex or oct
    switch (base) {
        case 8:
            str[i++] = '0';
            break;
        case 16:
            str[i++] = 'x';
            break;
        default:
            break;
    }
    
    if (!(i < bufferLen - 1)) {
        str[bufferLen - 1] = '\0';
        errno = EINVAL;
        return EINVAL;
    }

    if (sign < 0) {
        str[i++] = '-';
    }

    if (!(i < bufferLen - 1)) {
        str[bufferLen - 1] = '\0';
        errno = EINVAL;
        return EINVAL;
    }

    str[i] = '\0';

    Reverse(str);

    return 0;
}
