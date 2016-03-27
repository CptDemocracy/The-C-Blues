#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of input, and
 to delete entirely blank lines.
*/

#define BUFFER_INIT_CAPACITY 128

int main(int argc, const char** argv) {

    size_t bufferCapacity = BUFFER_INIT_CAPACITY;
    char* buffer = (char*)malloc(sizeof(char) * BUFFER_INIT_CAPACITY);
    if (!buffer) {
        errno = ENOMEM;
        return 1;
    }

    size_t bufferCount = 0;

    char prevc = 0;
    char currc = 0;

    while (1)
    {
        bufferCount = 0;
        memset(buffer, 0, sizeof(char) * bufferCapacity);

        printf(">>> ");

        currc = getchar();
        prevc = 0;
        while (currc != '\n') {            

            if (!(isblank(prevc) && isblank(currc))) 
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
                buffer[bufferCount] = currc;
                ++bufferCount;
            }
            
            prevc = currc;
            currc = getchar();
        }
        // don't really have to do it, since we always keep an extra
        // byte for the null terminating character and reset all bytes
        // to zeros at each iteration, however, we choose to play it
        // safe
        buffer[bufferCount] = 0;

        // eliminate blank lines
        size_t i = 0;
        while ((currc = buffer[i]) && isblank(currc)) {
            buffer[i] = 0;
            ++i;
        }

        printf("%s\n", buffer);
    }

    free(buffer);
    buffer = NULL;

    return 0;
}
