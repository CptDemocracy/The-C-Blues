#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-22. Write a program to "fold" long input lines into two or more shorter lines after
 the last non-blank character that occurs before the n-th column of input. Make sure your
 program does something intelligent with very long lines, and if there are no blanks or tabs
 before the specified column.
*/

#define BUFFER_INIT_CAPACITY    128
#define COLS_PER_LINE            10

int main(int argc, const char** argv) {

    size_t bufferCapacity = BUFFER_INIT_CAPACITY;
    char* buffer = (char*)malloc(sizeof(char) * BUFFER_INIT_CAPACITY);
    if (!buffer) {
        errno = ENOMEM;
        return 1;
    }

    size_t bufferCount = 0;

    char c = 0;
    size_t colCount = 0;

    while (1)
    {
        bufferCount = 0;
        colCount = 0;

        printf(">>> ");

        while ( (c = getchar()) != '\n') 
        {
            if (bufferCount >= bufferCapacity - 1)
            {
                // a safeguard in case someone accidentally changes bufferCapacity to 0
                bufferCapacity = (bufferCapacity > 0) ? bufferCapacity * 2 : BUFFER_INIT_CAPACITY;
                buffer = (char*)realloc(buffer, bufferCapacity);
                if (!buffer) {
                    errno = ENOMEM;
                    return 1;
                }
            }
            
            // word wrapping logic
            if (colCount >= COLS_PER_LINE) {
                colCount = 0;
                int i = bufferCount - 1;
                while (1)
                {
                    if (i <= 0) {
                        ungetc(c, stdin);
                        buffer[bufferCount] = '\n';    
                        break;
                    }
                    else if (isblank(buffer[i])) {
                        buffer[i] = '\n';
                        buffer[bufferCount] = c;
                        break;
                    }
                    --i;
                }
            }
            else {
                buffer[bufferCount] = c;                
                ++colCount;
            }
            ++bufferCount;
        }
        buffer[bufferCount] = 0;

        printf("%s\n", buffer);
    }

    free(buffer);
    buffer = NULL;

    return 0;
}
