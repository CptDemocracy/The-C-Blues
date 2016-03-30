#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 3-6. Write a version of itoa that accepts three 
 arguments instead of two. The third argument is a minimum 
 field width; the converted number must be padded with blanks 
 on the left if necessary to make it wide enough. 
 */

int Reverse(char* str);

int Itoa(int n, char s[], size_t padWidth);

int main(void) {
    
    char buffer[256] = { 0 };
    int n = 255;
    int paddingWidth = 24;
    Itoa(n, buffer, 24);
    printf("%s.\n", buffer);

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

int Itoa(int n, char s[], size_t padWidth) {
    if (!s) {
        errno = EINVAL;
        return EINVAL;
    }
    size_t i  = 0;
    int sign  = n;
    int digit = 0;
    if (sign >= 0) {
        do {
            digit = n % 10 + '0';
            s[i] = digit;
            ++i;
            n /= 10;
        } while (n > 0);
    } else {
        do {
            digit = -(n % 10) + '0';
            s[i] = digit;
            ++i;
            n /= 10;
        } while (n < 0);
    }
    
    size_t j = 0;
    while (j < padWidth) {
        s[j + i] = ' ';
        ++j;
    }
    i = j;
    
    s[i] = '\0';
    Reverse(s);

    return 0;
}
