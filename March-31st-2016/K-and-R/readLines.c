#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, 
 rather than calling alloc to maintain storage.
*/

#define BUFFER_SIZE 128

int ReadLines(FILE* stream, char* buffers[], size_t bufferLen, size_t buffersCount);

int main(void) {    
    
    char buffer1[BUFFER_SIZE] = { 0 };
    char buffer2[BUFFER_SIZE] = { 0 };
    char buffer3[BUFFER_SIZE] = { 0 };

    const int BUFFER_COUNT = 3;

    char* buffers[] = {
        buffer1, buffer2, buffer3
    };
    
    ReadLines(stdin, buffers, BUFFER_SIZE, BUFFER_COUNT);

    for (int i = 0; i < BUFFER_COUNT; ++i) {
        puts(buffers[i]);
    }

    getchar();
    return 0;
}

int ReadLines(FILE* stream, char* buffers[], size_t bufferLen, size_t buffersCount) {
    if (!stream | !buffers || bufferLen < 1) {
        return 1;
    }
    for (size_t i = 0; i < buffersCount; ++i) {
        if (!buffers[i]) {
            return 1;
        }
        fgets(buffers[i], bufferLen, stream);
        if (buffers[i][strlen(buffers[i]) - 1] == '\n') {
            buffers[i][strlen(buffers[i]) - 1] = '\0';
        }
    }
    return 0;
}
