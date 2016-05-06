/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.121

Programming Project 1 in Chapter 4 asked you to write
a program that displays a two-digit number with its
digits reversed. Generalize the program so that the
number can have one, two, three, or more digits.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_INIT_CAPACITY 4

int Reverse(void* buffer, size_t elemSize, size_t count);

int main(void) 
{
    int capacity = BUFFER_INIT_CAPACITY;
    char* buffer = (char*)calloc(capacity, sizeof(char));
    if (!buffer) {
        return EXIT_FAILURE;
    }
    int count = 0;
    char c = '\0';
    int isValid = 0;

    while (!isValid)
    {
        printf("Please enter an integer you want reversed: ");

        isValid = 1;
        while ( (c = getchar()) != '\n' && c != EOF) 
        {
            // make sure we have an extra byte to store the null-terminating
            // character
            if (count + 1 >= capacity) {
                int newCapacity = (capacity > 0) ? capacity * 2 : BUFFER_INIT_CAPACITY;
                char* newBuffer = (char*)calloc(newCapacity, sizeof(char));
                if (!newBuffer) {
                    return EXIT_FAILURE;
                }
                memcpy(newBuffer, buffer, sizeof(char) * count);
                free(buffer);

                buffer = newBuffer;
                capacity = newCapacity;
            }

            if (isdigit(c)) {
                buffer[count] = c;
                ++count;
            } else {
                // cannot break out on the spot, since we still
                // need to consume the rest of input
                isValid = 0;
            }
        }
        // if empty, prompt for input again
        if (count == 0) isValid = 0;

        // we've provided we have enough storage to store the 
        // null-terminating character, so no bound error here
        buffer[count] = '\0';

        if (!isValid) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            // reset the count, overwrite the buffer
            count = 0;
        }
    }
    Reverse((char*)buffer, sizeof(char), count);
    printf("Reversed: %s\n", buffer);
    free(buffer);

    getchar();
    return EXIT_SUCCESS;
}

int Reverse(void* buffer, size_t elemSize, size_t count) {
    if (!buffer) {
        return 1;
    }
    if (elemSize < 1) {
        return 2;
    }
    void* tempBuffer = calloc(1, elemSize);
    
    if (!tempBuffer) {
        return 3;
    }
    char* beginPtr = (char*)buffer;
    char* endPtr   = (char*)buffer + elemSize * (count - 1);

    while (beginPtr < endPtr) 
    {
        memcpy(tempBuffer, beginPtr, elemSize);
        memcpy(beginPtr, endPtr, elemSize);
        memcpy(endPtr, tempBuffer, elemSize);
        beginPtr += elemSize;
        endPtr     -= elemSize;
    }
    free(tempBuffer);

    return 0;
}
