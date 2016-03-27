#define _CRT_DBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "NameSpace.h"

#define CHAR_BUFFER_SIZE 32

char CHAR_BUFFER[CHAR_BUFFER_SIZE];

long ReadLongInt(void) {

    const int BUFFER_CAPACITY_MULTIPLIER = 2;
    const int BUFFER_DEFAULT_CAPACITY = 4;
    const int DECIMAL_RADIX = 10;
    const long RETURN_VALUE_ON_ERROR = 0L;

    int bufferCapacity = BUFFER_DEFAULT_CAPACITY;
    char* buffer = calloc(bufferCapacity, sizeof(char));
    if (!buffer) {
        errno = ENOMEM;
        return RETURN_VALUE_ON_ERROR;
    }

    int inputLen = 0;
    long value   = 0L;
    int isValid  = 1;

    while (1) 
    {
        if (!isValid) {
            printf("Input invalid.\n");
            fflush(stdout);
            errno = 0;
        }
        isValid = 1;
        inputLen = 0;

        while (1) {
            if (inputLen >= bufferCapacity - 1) {
                int newBufferCapacity = (bufferCapacity > 0) ? 
                    bufferCapacity * BUFFER_CAPACITY_MULTIPLIER : BUFFER_DEFAULT_CAPACITY;
                char* newBuffer = calloc(newBufferCapacity, sizeof(char));
                if (!newBuffer) {
                    errno = ENOMEM;
                    return RETURN_VALUE_ON_ERROR;
                }
                memcpy(newBuffer, buffer, inputLen);
                
                // !!!
                free(buffer);

                buffer = newBuffer;
                bufferCapacity = newBufferCapacity;
            }
            char c = fgetc(stdin);
            if (c == '\n' || c == '\0' || c == EOF) {
                break;
            }
            buffer[inputLen] = c;
            ++inputLen;
        }
        buffer[inputLen] = '\0';
        
        if (!isValid) {
            continue;
        }
        
        // skip past whitespace so that at a later point, by subtracting
        // pBegin from pParseEnd and comparing it to inputLen, we could
        // test whether value supplied by user was indeed in a valid 
        // format
        char* pBegin = buffer;
        while (inputLen > 0 && isblank(*pBegin)) {
            ++pBegin;
            --inputLen;
        }

        // input empty or all blanks
        if (inputLen <= 0) {
            isValid = 0;
            continue;
        }

        char* pParseEnd = NULL;
        value = strtol(pBegin, &pParseEnd, DECIMAL_RADIX);
        
        if (pParseEnd - pBegin < inputLen) {
            isValid = 0;
            continue;
        }
        
        // if user entered a value that causes long type to
        // overflow and strtol notified us about it by setting
        // errno to ERANGE
        if (errno == ERANGE) {
            isValid = 0;
            continue;
        }

        break;
    }
    return value;
}

int cmpInts(const int* a_ptr, const int* b_ptr) {
    int a = *a_ptr;
    int b = *b_ptr;
    return (a == b) ? (0) : ((a > b) ? 1 : -1);
}

int main(void) 
{
    int arr[20] = { 1, 1, 1, 1, 1, 1 };
    const int ARRAY_LENGTH = 6;

    do {
        ns.qsort(arr, ARRAY_LENGTH, sizeof(int), cmpInts);
        
        for (int i = 0; i < ARRAY_LENGTH; ++i) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        for (int i = 0; i < ARRAY_LENGTH; ++i) {
            arr[i] = rand() % ARRAY_LENGTH;
        }

        getchar();
    } while (1);

    printf("Success...\n");
    getchar();

    return 0;
}
