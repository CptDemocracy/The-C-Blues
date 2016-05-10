/*
K.N.King "C Programming. A Modern Approach."
Programming project 2 p.274

"Enter a message: He lived as a devil, eh?
Palindrome

Enter a message: Madam, I am Adam.
Not a palindrome
"

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "DynamicBuffer.h"

int IsPalindrome(const char* s, int caseSensitive);

int main(void) {
    
    struct DynamicBuffer dynbuffer = { 0 };
    if (DynamicBufferNew(&dynbuffer) != 0) {
        return EXIT_FAILURE;
    }

    const char* input = NULL;
    int isCaseSensitive = 0;
    int isPalindrome = 0;
    int shouldQuit = 0;
    
    while (!shouldQuit) {
        printf("Please enter a message (or 'q' to quit): ");
        input = DynamicBufferGetString(&dynbuffer);    
        if (strcmp(input, "q") != 0 || strcmp(input, "Q") != 0) {
            puts("Thank you for using our application!");
            shouldQuit = 1;
        } else {
            isPalindrome = IsPalindrome(input, isCaseSensitive);
            printf("%sa palindrome.\n", isPalindrome ? "Is " : "Not ");
        }
        (void) DynamicBufferClear(&dynbuffer);
    }

    DynamicBufferDispose(&dynbuffer);

    getchar();
    return EXIT_SUCCESS;
}

int IsPalindrome(const char* s, int caseSensitive) {
    if (!s) {
        return 1;
    }
    int isPalindrome = 1;

    const char* end = &s[strlen(s) - 1];
    if (s == end) {
        isPalindrome = 0;
    } else {
        while (s < end) {
            if (!isalpha(*s)) {
                ++s;
            }
            else if (!isalpha(*end)) {
                --end;
            }
            else if ((caseSensitive && *s != *end)
                 || (!caseSensitive && tolower(*s) != tolower(*end))) 
            {
                isPalindrome = 0;
                break;
            }
            else {
                ++s; --end;
            }
        }
    }
    return isPalindrome;
}
