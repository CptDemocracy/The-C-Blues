#include <string.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-4. Write the function strend(s,t), which returns 1 if the 
 string t occurs at the end of the string s, and zero otherwise.
*/

#define BUFFER_SIZE 256

int Strend(const char* s, const char* t) {
    if (!s || !t) {
        return 0;
    }
    const char* ptchar = t;
    while (*s != 0) {
        if (*s == *ptchar) {
            ++ptchar;
        }
        else {
            ptchar = t;
        }        
        ++s;
    }
    if (!*s && !*ptchar) {
        return 1;
    }
    return 0;
}

int main(void) {    

    char buffer[BUFFER_SIZE] = { 0 };

    int ret = 0;
    ret = Strend("abcd", "bc"); // 0
    ret = Strend("abcd", "cd"); // 1
    ret = Strend("abcd", "abcde"); // 0

    getchar();
    return 0;
}
