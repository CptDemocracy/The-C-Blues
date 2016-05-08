/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.177

The prototypical Internet newbie is a fellow named B1FF, who
has a unique way of writing messages. Here's a typical B1FF 
communique:

H3Y DUD3, C 15 R1LLY C00L!!!!!!!!!!

Write a "B1FF filter" that reads a message entered by the
user and translates it into B1FF-speak:

"Enter message: Hey dude, C is rilly cool
In B1FF-speak: H3Y DUD3, C 15 R1LLY C00L!!!!!!!!!!
"

Your program should convert the message to uppercase letters,
substitute digits for certain letters:
A -> 4
B -> 8
E -> 3
I -> 1
O -> 0
S -> 5
and then append 10 exclamation marks.
*/

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    const char TRANSLATION_TABLE[UCHAR_MAX] = {
        ['A'] = '4', ['a'] = '4',
        ['B'] = '8', ['b'] = '8',
        ['E'] = '3', ['e'] = '3',
        ['I'] = '1', ['i'] = '1',
        ['O'] = '0', ['o'] = '0',
        ['S'] = '5', ['s'] = '5',
    };
    const int EXCLAMATION_MARK_COUNT = 10;

    char c = '\0';

    while ( (c = getchar()) != '\n' && c != EOF) {
        if (TRANSLATION_TABLE[c]) {
            putchar(TRANSLATION_TABLE[c]);
        } else {
            putchar(c);
        }
    }
    for (int i = 0; i < EXCLAMATION_MARK_COUNT; ++i) {
        putchar('!');
    }
    putchar('\n');

    getchar();
    return EXIT_SUCCESS;
}
