#include <limits.h>
#include <stdio.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-4. Write an alternative version of squeeze(s1,s2) 
 that deletes each character in s1 that matches any character 
 in the string s2. 

 */

// O(n) solution
int Squeeze(char* s1, const char* s2) {
    if (!s1 || !s2) {
        errno = EINVAL;
        return EINVAL;
    }

    // dictionary for O(1) char lookup
    int chars[UCHAR_MAX] = { 0 };
    
    // save chars in s2 to the dictionary
    const char* pchar2 = &s2[0];
    while (*pchar2) {
        chars[(unsigned char)(*pchar2)] = 1;
        ++pchar2;
    }

    char* pchar0 = &s1[0];
    char* pchar1 = &s1[0];
    while (*pchar1) {

        // do not be tempted to move ++pchar1 out of the if-else
        // blocks, if you do, make sure you test pchar1 for zero
        // char and break out on zero char immediately or else 
        // you will go past the end of the string corrupting
        // memory as you go

        if (chars[(unsigned char)(*pchar1)]) {
            ++pchar1;
        } else {
            *pchar0 = *pchar1;
            ++pchar0;
            ++pchar1;
        }        
    }
    *pchar0 = '\0';

    return 0;
}

int main(void) {

    char s1[] = "C provides six operators for bit manipulation;"
                "these may only be applied to integral operands,"
                "that is, char, short, int, and long, whether signed or unsigned.";
    const char* s2 = "aeiou";
    
    // remove vowels
    Squeeze(s1, s2);
    printf("%s\n", s1);

    getchar();

    return 0;
}
