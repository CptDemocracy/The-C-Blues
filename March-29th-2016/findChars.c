#include <limits.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-5. Write the function any(s1,s2), which returns 
 the first location in a string s1 where any character from 
 the string s2 occurs, or -1 if s1 contains no characters from s2.
 (The standard library function strpbrk does the same job but 
 returns a pointer to the location.) 

 */

int Any(const char* s1, const char* s2) {
    if (!s1 || !s2) {
        errno = EINVAL;
        return -1;
    }
    
    // setup a dictionary for O(n) access to s2's chars
    int chars[UCHAR_MAX] = { 0 };

    int i = 0;
    for (i = 0; s2[i] != '\0'; ++i) {
        chars[(unsigned char)(s2[i])] = 1;
    }

    for (i = 0; s1[i] != '\0'; ++i) {
        if (chars[(unsigned char)(s1[i])]) {
            return i;        
        }
    }
    
    return -1;
}

int AnyWithPredicate(const char* str, int(*pred)(int)) {
    if (!str || !pred) {
        errno = EINVAL;
        return -1;
    }
    for (int i = 0; str[i] != '\0'; ++i) {
        if ((*pred)(str[i])) {
            return i;
        }
    }
    return -1;
}

int main(void) {

    const char* s1 = "\"Would you tell me, please, which way I ought to go from here?\""
                    " - \"That depends a good deal on where you want to get to.\"";

    const char* s2 = "aeiou"; // find the first vowel

    int firstVowelIndex = Any(s1, s2);
    printf("The first vowel in the text is at index %d.\n", firstVowelIndex);

    int firstPunctIndex = AnyWithPredicate(s1, ispunct);
    printf("The first punctuation character in the text is at index %d.\n", firstPunctIndex);

    getchar();

    return 0;
}
