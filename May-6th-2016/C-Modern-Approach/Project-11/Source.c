/*
K.N.King "C Programming. A Modern Approach."
Programming project 11 p.157

Write a program that takes a first name and
last name entered by the user and displays
the last name, a comma and the first initial,
followed by a period:

"Enter a first and last name: Lloyd Fosdick
Fosdick, L.
"

The user's input may contain extra spaces
fore the first name, between the first and
last names, and after the last name.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE 256

int main(void) 
{
    char buffer[BUFFER_SIZE] = { 0 };
    char c = '\0';
    char* pchar = NULL;
    char* firstName = NULL;
    char* lastName = NULL;
    int isValid = 0;
    while (!isValid)
    {
        printf("Please enter a first and last name: ");
        if (!fgets(buffer, BUFFER_SIZE, stdin)) {
            return EXIT_FAILURE;
        }
        // if users entered more data than our buffer can
        // accommodate, discard excessive input
        // that can be detected if the last non-null character
        // in the buffer is not a new line character
        if (buffer[strlen(buffer) - 1] != '\n') {
            while ((c = getchar()) != '\n' && c != EOF) continue;
        }
        // trim off the new line character
        buffer[strlen(buffer) - 1] = '\0';

        // validate user input        
        pchar = buffer;        

        // skip past whitespace in the beginning
        // of the input string
        while (isspace(*pchar)) ++pchar;
        isValid = 1;

        firstName = pchar;

        // validate the rest of the string
        while ((c = *pchar) != '\0') {
            if (!isalpha(c) && !isspace(c)) {
                isValid = 0;
                break;
            }
            ++pchar;
        }
        if (!isValid) {
            fprintf(
                stderr,    
                "Input invalid. Make sure your name "
                "only contains alphabetical characters.");
        }
    }
    // a last name could be more than one word,
    // for example, "van Dijkstra", locate the
    // beginning of the last name by first setting
    // the pointer back to where we found the first
    // name
    pchar = firstName;
    // skip past the first name
    while (isalpha(*pchar)) ++pchar;
    // zero-terminate firstName
    *pchar = '\0';
    ++pchar;
    // skip past white space
    while (isspace(*pchar)) ++pchar;
    // pchar now points to the last name
    lastName = pchar;
    // capitalize the last name. 
    // this is required for surnames like "van Dijkstra"
    // where the "van" part is not usually capitalized,
    // but should be capitalized if in the beginning of
    // a sentence
    lastName[0] = toupper(lastName[0]);

    // output the data
    printf("%s, %c.\n", lastName, firstName[0]);

    getchar();
    return EXIT_SUCCESS;
}
