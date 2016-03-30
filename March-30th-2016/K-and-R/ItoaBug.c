#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 3-4. In a two's complement number representation, our version 
 of itoa does not handle the largest negative number, that is, the value 
 of n equal to -(2wordsize-1). Explain why not. Modify it to print that 
 value correctly, regardless of the machine on which it runs. 

// Itoa: convert n to characters in s
void Itoa(int n, char s[])
{
    int i, sign;
    if ((sign = n) < 0) // record sign
        n = -n; // make n positive
    i = 0;
    do { // generate digits in reverse order
        s[i++] = n % 10 + '0'; // get next digit
    } while ((n /= 10) > 0); // delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    Reverse(s);
}

 The reason our Itoa didn't work with the largest negative number is
 because it uses only one MSB bit set, and when we apply NOT and add 
 1 to invert (in a two's complement system), it simply overwraps and
 gives exactly the same number, that is: INT_MIN == -INT_MIN
 
 The solution is to not invert negative numbers, instead introduce
 extra breaking logic in the while loop based on the sign value.

 */

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

 /* Itoa: convert n to characters in s */
void Itoa(int n, char s[])
{
    int i, sign;
    sign = n;
    i = 0;
    do { /* generate digits in reverse order */
        int digit = (sign < 0) ? -(n % 10) + '0' : n % 10 + '0';
        s[i++] = digit; /* get next digit */    
    } while (!(sign >= 0 && (n /= 10) <= 0) &&
            !(sign < 0 && (n /= 10) >= 0));
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    Reverse(s);
}

int main(void) {
    
    char buffer[256] = { 0 };
    // comment
    int n = INT_MIN;
    Itoa(n, buffer);

    printf("%s\n", buffer);

    n = INT_MIN + 1;
    Itoa(n, buffer);

    printf("%s\n", buffer);

    getchar();
    return 0;
}
