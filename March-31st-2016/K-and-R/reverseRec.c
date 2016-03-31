#include <string.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 4-13. Write a recursive version of the function reverse(s), 
 which reverses the string s in place.
*/

#define BUFFER_SIZE 256

static char BUFFER[BUFFER_SIZE];

static int ItoaHelper(int n, char* buffer, size_t bufferLen);

static int ReverseHelper(char* begin, char* end);

int Reverse(char* s) {
    if (!s) {
        return 1;
    }
    size_t len = strlen(s);
    ReverseHelper(&s[0], &s[len]);
    return 0;
}

int ReverseHelper(char* begin, char* end) {
    if (!begin || !end) {
        return 1;
    }
    if (begin < end) {
        char temp = end[-1];
        end[-1] = begin[0];
        begin[0] = temp;
        ReverseHelper(begin + 1, end - 1);
    }
    return 0;
}

int Itoa(int n, char* buffer, size_t bufferLen) {
    if (!buffer) {
        return 1;
    }
    ItoaHelper(n, buffer, bufferLen);
    Reverse(buffer);
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
