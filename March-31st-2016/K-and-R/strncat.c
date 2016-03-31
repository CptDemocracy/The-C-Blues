#include <string.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-3. Write a pointer version of the function strcat that we 
 showed in Chapter 2: strcat(s,t) copies the string t to the end of s.
*/

#define BUFFER_SIZE 256

char* Strcat(char* dest, const char* src) {
    if (!dest || !src) {
        return NULL;
    }
    while (*dest) {
        ++dest;
    }
    while (1) {
        *dest = *src;
        if (!*src) {
            break;
        }
        ++dest, ++src;
    }
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    if (!dest || !src) {
        return NULL;
    }
    while (*dest) {
        ++dest;
    }
    size_t i = 0;
    while (*src != 0 && i < count) {
        *dest = *src;
        ++dest, ++src, ++i;
    }
    *dest = 0;
    return dest;
}

int main(void) {    

    char buffer[BUFFER_SIZE] = { 0 };

    strcpy(buffer, "These ");
    Strcat(buffer, "strings ");
    Strcat(buffer, "are ");
    Strcat(buffer, "concatenated");
    printf("%s.\n", buffer);

    getchar();
    return 0;
}
