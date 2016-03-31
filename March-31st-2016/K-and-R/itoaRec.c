#include <string.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; 
 that is, convert an integer into a string by calling a recursive routine.
*/

#define BUFFER_SIZE 256

static char BUFFER[BUFFER_SIZE];

static int ItoaHelper(int n, char* buffer, size_t bufferLen);

int Itoa(int n, char* buffer, size_t bufferLen) {
    if (!buffer) {
        return 1;
    }
    ItoaHelper(n, buffer, bufferLen);
    char temp = 0;
    size_t len = strlen(buffer);
    for (size_t i = 1, j = len; i < j; ++i, --j) {
        temp = buffer[i - 1];
        buffer[i - 1] = buffer[j - 1];
        buffer[j - 1] = temp;
    }
    return 0;
}

static int ItoaHelper(int n, char* buffer, size_t bufferLen) {
    if (!buffer) {
        return 1;
    }    
    if (bufferLen < 2) {
        buffer[0] = '\0';
    }
    buffer[0] = n % 10 + '0';
    buffer[1] = '\0';
    if (n / 10 > 0) {
        ItoaHelper(n / 10, buffer + 1, bufferLen - 1);        
    }    
    return 0;
}

int main(void) {
    Itoa(123456789, BUFFER, BUFFER_SIZE);
    printf("%s\n", BUFFER);

    Itoa(0, BUFFER, 256);
    printf("%s\n", BUFFER);

    getchar();
    return 0;
}
