#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 4-1. Write the function strindex(s,t) which returns 
 the position of the rightmosT occurrence of t in s, or -1 if 
 there is none. 
 */

#define ERROR        -2
#define NOT_FOUND    -1

int KMP(const char* str, int strLen, const char* pattern, int patternLen);

int KMPComputeDFA(const char* pattern, int patternLen, int* OutDFA);

int KMPReversedComputeDFA(const char* pattern, int patternLen, int* OutDFA);

int KMPReversed(const char* str, int strLen, const char* pattern, int patternLen);

int StrIndex(const char* text, const char* pattern);

int main(void) {
    
    const char* OUTPUT_FORMAT_FOUND = "Substring \"%s\" was found at index %d in string \"%s\""
                                      " in a reversed search.\n";

    const char* OUTPUT_FORMAT_NOT_FOUND = "Substring \"%s\" was not found in string \"%s\".\n";

    const char* txt1 = "aaaeeaaaeeebxyyz";
    const char* pat1_1 = "aaaeee";
    const char* pat1_2 = "yyz";
    const char* pat1_3 = "bca";

    const char* txt2 = "foofooofooofoobafoobarbabaz";
    const char* pat2_1 = "foofo";
    const char* pat2_2 = "ofoo";
    const char* pat2_3 = "ogoo";

    int index = 0;

    index = StrIndex(txt1, pat1_1);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat1_1, index, txt1);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat1_1, txt1);
    }
    
    index = StrIndex(txt1, pat1_2);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat1_2, index, txt1);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat1_2, txt1);
    }

    index = StrIndex(txt1, pat1_3);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat1_3, index, txt1);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat1_3, txt1);
    }

    index = StrIndex(txt2, pat2_1);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat2_1, index, txt2);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat2_1, txt2);
    }
    
    index = StrIndex(txt2, pat2_2);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat2_2, index, txt2);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat2_2, txt2);
    }

    index = StrIndex(txt1, pat2_3);
    if (index != NOT_FOUND) {
        printf(OUTPUT_FORMAT_FOUND, pat2_3, index, txt2);
    } else {
        printf(OUTPUT_FORMAT_NOT_FOUND, pat2_3, txt2);
    }

    getchar();

    return 0;
}

int KMPComputeDFA(const char* pattern, int patternLen, int* OutDFA) {
    if (!pattern || patternLen < 1 || !OutDFA) {
        errno = EINVAL;
        return EINVAL;
    }
    int k = -1;
    OutDFA[0] = k;
    for (int i = 1; i < patternLen; ++i) {
        while (k > 0 && pattern[i] != pattern[k + 1]) {
            k = OutDFA[k];
        }
        if (pattern[i] == pattern[k + 1]) {
            ++k;
        }
        OutDFA[i] = k;
    }
    return 0;
}

int KMP(const char* str, int strLen, const char* pattern, int patternLen) {

    if (!str || strLen < 1 || !pattern || patternLen < 1) {
        errno = EINVAL;
        return ERROR;
    }
    
    int* dfa = (int*)calloc(patternLen, sizeof(int));
    if (!dfa) {
        errno = ENOMEM;
        return ERROR;
    }

    KMPComputeDFA(pattern, patternLen, dfa);
    
    int k = -1;
    for (int i = 0; i < strLen; ++i) {
        while (k > -1 && str[i] != pattern[k + 1]) {
            k = dfa[k];
        }
        if (str[i] == pattern[k + 1]) {
            ++k;
        }
        if (k == patternLen - 1) {
            free(dfa);
            return i - k;
        }
    }
    free(dfa);
    return NOT_FOUND;
}

int KMPReversedComputeDFA(const char* pattern, int patternLen, int* OutDFA) {
    if (!pattern || patternLen < 1 || !OutDFA) {
        errno = EINVAL;
        return EINVAL;
    }
    int k = patternLen;
    OutDFA[patternLen - 1] = k;
    for (int i = patternLen - 2; i >= 0; --i) {
        while (k < patternLen && pattern[i] != pattern[k - 1]) {
            k = OutDFA[k];
        }
        if (pattern[i] == pattern[k - 1]) {
            --k;
        }
        OutDFA[i] = k;
    }
    return 0;
}

int KMPReversed(const char* str, int strLen, const char* pattern, int patternLen) {

    if (!str || strLen < 1 || !pattern || patternLen < 1) {
        errno = EINVAL;
        return ERROR;
    }

    int* dfa = (int*)calloc(patternLen, sizeof(int));
    if (!dfa) {
        errno = ENOMEM;
        return ERROR;
    }

    KMPReversedComputeDFA(pattern, patternLen, dfa);
    
    int k = patternLen;
    for (int i = strLen - 1; i >= 0; --i) {
        while (k < patternLen && str[i] != pattern[k - 1]) {
            k = dfa[k];
        }
        if (str[i] == pattern[k - 1]) {
            --k;
        }
        if (k <= 0) {
            free(dfa);
            return i - k;
        }
    }

    free(dfa);
    return NOT_FOUND;
}

int StrIndex(const char* text, const char* pattern) {
    if (!text || !pattern) {
        errno = EINVAL;
        return ERROR;
    }
    return KMPReversed(text, strlen(text), pattern, strlen(pattern));
}
