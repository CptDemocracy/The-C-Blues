#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "strmanip.h"

#define ERROR        -2
#define NOT_FOUND    -1

int CountWords(const char* text) {
    
    if (!text) {
        errno = EINVAL;
        return -1;
    }

    int count = 0;
    const char* pChar = text;
    while (*pChar != '\0') {
        while (isblank(*pChar)) {
            ++pChar;
        }
        if (*pChar == '\0') {
            break;
        }
        ++count;
        while (*pChar != '\0' && !isblank(*pChar)) {
            ++pChar;
        }
    }
    return count;
}

int Substring(const char* text, 
    int start, 
    int count, 
    char* OutResult) {
    if (!text) {
        errno = EINVAL;
        return 0;
    }
    if (!OutResult) {
        errno = EINVAL;
        return 0;
    }
    int i = 0;
    while (i < count) {
        if (text[start + i] == '\0') {
            break;
        }
        OutResult[i] = text[start + i];
        ++i;
    }
    OutResult[i] = '\0';
    return i;
}

int IsSubstringOf(const char* target, const char* substring) {
    if (!target) {
        errno = EINVAL;
        return 0;
    }
    if (!substring) {
        errno = EINVAL;
        return 0;
    }    
    return KMP(target, 0, strlen(target), substring, strlen(substring)) >= 0;
}

int FindString(const char* target, const char* substring) {
    // Did a research on the KMP to guarantee an O(n) time complexity
    // Used the following code for reference:
    //        code.activestate.com/recipes/577908-implementation-of-knuthmorrispratt-algorithm
    // Had to memorize it by rote to understand. The concept itself is fairly straightforward
    // but the implementation can be quite tricky.
    // Tweaked the code a little bit to avoid passing dynamic memory between functions
    // which, I believe, can easily complicate the code readability and maintenance.
    // Whenever possible, make it each function's responsibility to deallocate the dynamic
    // memory it requested.

    if (!target) {
        errno = EINVAL;
        return ERROR;
    }
    if (!substring) {
        errno = EINVAL;
        return ERROR;
    }
    return KMP(target, 0, strlen(target), substring, strlen(substring));
}

int* KMPCalculateDFA(const char* pattern, 
    int patternLen, 
    int* dfa) 
{

    // NULL passed instead of a cstring
    if (!pattern) {
        errno = EINVAL;
        return NULL;
    }
    // argument out of range
    if (patternLen <= 0) {
        errno = EINVAL;
        return NULL;
    }
    // NULL passed instead of a pointer to the DFA table
    if (!dfa) {
        errno = EINVAL;
        return NULL;
    }
    int k  = -1;
    dfa[0] = k;
    for (int i = 1; i < patternLen; ++i) {
        while (k > -1 && pattern[i] != pattern[k + 1]) {
            k = dfa[k];
        }
        if (pattern[i] == pattern[k + 1]) {
            ++k;
        }
        dfa[i] = k;
    }
    return dfa;
}

int KMP(const char* source, 
    int start, 
    int sourceLen, 
    const char* pattern, 
    int patternLen) 
{

    if (!source || !pattern) {
        errno = EINVAL;
        return ERROR;
    }
    if (sourceLen  <= 0 ||
        patternLen <= 0) 
    {
        errno = EINVAL;
        return ERROR;
    }
    if (start < 0 || start >= sourceLen) {
        errno = EINVAL;
        return ERROR;
    }

    source += start;

    int* dfa = calloc(patternLen, sizeof(int));
    if (!dfa) {
        errno = ENOMEM;
        return ERROR;
    }
    KMPCalculateDFA(pattern, patternLen, dfa);
    int k = -1;
    for (int i = 0; i < sourceLen; ++i) {
        while (k > -1 && source[i] != pattern[k + 1]) {
            k = dfa[k];
        }
        if (source[i] == pattern[k + 1]) {
            ++k;
        }
        if (k == patternLen - 1) {
            free(dfa);
            return i - k + start;
        }
    }
    free(dfa);
    return NOT_FOUND;
}

int RemoveString(char* text, int start, int count) {
    
    if (!text) {
        errno = EINVAL;
        return ERROR;
    }
    
    if (start < 0) {
        errno = EINVAL;
        return ERROR;
    }

    if (count < 0) {
        errno = EINVAL;
        return ERROR;
    }

    size_t textLenUnsigned = strlen(text);
    
    // we choose to not support strings of length
    // greater than INT_MAX
    if (textLenUnsigned > (size_t)INT_MAX) {
        errno = EDOM;
        return ERROR;
    }

    int textLen = (int)textLenUnsigned;

    if (start + count > textLen) {
        errno = EINVAL;
        return ERROR;
    }

    // we allow clients to call this function with arguments to 
    // start and count equal to zero, which renders memcpy or 
    // strcpy or strncpy a no-no, consider a call:
    //        RemoveString(cstr, 0, 0);
    // then memmove will be called like this:
    //        memmove(&text[0], &text[0 + 0], 0 * sizeof(char))
    // this will cause data to overlap
    memmove(&text[start], 
            &text[start + count], 
            count * sizeof(char));
    
    int endIndex   = textLen - count;
    text[endIndex] = '\0';
    
    // sanitize the non-overwritten end of the string
    // to prevent loitering
    memset(&text[endIndex], 0, count);

    return 0;
}

int InsertString(const char* source, 
    const char* insert, 
    int index, 
    char* OutResult) 
{
    if (!source || !index || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }
    if (index < 0) {
        errno = EINVAL;
        return ERROR;
    }

    size_t sourceLen = strlen(source);
    size_t insertLen = strlen(insert);

    // we choose to not support strings of length
    // greater than INT_MAX
    if (sourceLen + insertLen > (size_t)INT_MAX) {
        errno = EDOM;
        return ERROR;
    }

    strncpy(&OutResult[0], &source[0], index);
    strncpy(&OutResult[index], &insert[0], insertLen);
    strncpy(&OutResult[index + insertLen], &source[index], sourceLen - index);
    OutResult[sourceLen + insertLen] = '\0';
    
    return (int)(sourceLen + insertLen);
}

int FindSubstring(const char* source, 
    const char* substring, 
    int start) 
{

    if (!source || !substring) {
        errno = EINVAL;
        return ERROR;
    }
    if (start < 0) {
        errno = EINVAL;
        return ERROR;
    }
    return KMP(source, start, strlen(source), substring, strlen(substring));
}

int ReplaceFirstSubstring(const char* source,
    const char* target,
    const char* replac,
    char* OutResult)
{
    
    if (!source || !target || !replac || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    int sourceLen = strlen(source);
    int targetLen = strlen(target);
    int replacLen = strlen(replac);
    int start = 0;

    int i = FindSubstring(source, target, start);
    
    if (i >= 0) {
        strncpy(OutResult, source, i);
        strncpy(&OutResult[i], replac, replacLen);
        strncpy(&OutResult[i + replacLen], 
                &source[i + targetLen], 
                sourceLen - i - targetLen + 1);
        return 1;
    }
    strncpy(OutResult, source, sourceLen + 1);
    return 0;
}

int ReplaceAllSubstrings(const char* source, 
    const char* target, 
    const char* replac, 
    char* OutResult) 
{
    
    if (!source || !target || !replac || !OutResult) {
        errno = EINVAL;
        return ERROR;
    }

    int i = -1;
    int j = 0;
    int replCount = 0;
    int resultLen = 0;
    int sourceLen = strlen(source);
    int targetLen = strlen(target);
    int replacLen = strlen(replac);
    while ( (i = FindSubstring(source, target, i + 1) ) >= 0) {
        
        strncpy(&OutResult[resultLen], &source[j], i - j);
        resultLen += i - j;
        
        strncpy(&OutResult[resultLen], replac, replacLen);
        resultLen += replacLen;

        ++replCount;
        j = i + targetLen;
    }
    if (resultLen > 0) {
        strncpy(&OutResult[resultLen], &source[j], sourceLen - j);
        resultLen += sourceLen - j;
        OutResult[resultLen] = '\0';
    } else {
        // if no substrings were found to replace, copy the
        // whole source and append a null terminating char 
        strncpy(OutResult, source, sourceLen + 1);
    }
    return replCount;
}
