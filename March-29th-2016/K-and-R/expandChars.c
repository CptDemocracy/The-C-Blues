#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
 the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case
 and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
 leading or trailing - is taken literally.
*/

int Expand(char* buffer, size_t bufferLen, const char* str);

int main(void) {

    char buffer[256]; // = { 0 };
    const char* str = "0-9";
    Expand(buffer, 256, str);
    printf("%s.\n", buffer);

    getchar();
    return 0;
}

int Expand(char* buffer, size_t bufferLen, const char* str) {
    if (!buffer || bufferLen == 0 || !str) {
        errno = EINVAL;
        return EINVAL;
    }
    
    const char* pchar = &str[0];

    // skip whitespace
    while (isblank(*pchar)) ++pchar;

    // if not alnum, report error
    if (!isalnum(*pchar)) {
        errno = EINVAL;
        return EINVAL;
    }

    char start = *pchar;
    ++pchar;

    if (*pchar != '-') {
        errno = EINVAL;
        return EINVAL;
    }

    ++pchar;
    
    // at this point one might be wondering why we 
    // are not testing for the null terminating char,
    // the truth is we don't really have to, since
    // the null terminating character won't pass
    // checks for alnum and equality with the dash
    // character
    if (!isalnum(*pchar)) {
        errno = EINVAL;
        return EINVAL;
    }

    char end = *pchar;

    ++pchar;

    // make sure the rest of the string is clear,
    // if not, report error, we don't want our
    // clients to have any surprises
    while (isblank(*pchar)) ++pchar;

    if (*pchar != '\0') {
        errno = EINVAL;
        return EINVAL;
    }
    
    // unfold the sequence
    size_t i = 0;
    char c = start;
    char* pbuffer = &buffer[0]; 
    
    while (i < bufferLen - 1 && c <= end) {
        *pbuffer = c;
        ++pbuffer;
        ++c;
    }

    *pbuffer = '\0';

    return 0;
}
