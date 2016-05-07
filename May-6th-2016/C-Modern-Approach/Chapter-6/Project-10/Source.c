/*
K.N.King "C Programming. A Modern Approach."
Programming project 10 p.157

Write a program that counts the number of vowels 
(a, e, i, o, and u) in a sentence:

"Enter a sentence: And that's the way it is.
Your sentence contains 6 vowels.
"
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int IsVowel(char c);

int main(void) {
    char c = '\0';
    int count = 0;
    printf("Enter a sentence: ");
    while ( (c = getchar()) != '\n' && c != EOF) {
        if (IsVowel(c)) {
            ++count;
        }
    }
    printf("Your sentence contains %d vowels.\n", count);
    getchar();
    return EXIT_SUCCESS;
}

int IsVowel(char c) {
    c = tolower(c);
    return c == 'a'
        || c == 'e'
        || c == 'i'
        || c == 'o'
        || c == 'u';
}
