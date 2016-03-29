#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab into
 visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a
 function for the other direction as well, converting escape sequences into the real characters.
*/

int Escape(const char* str, char* OutResult, size_t OutResultLen);

int Unescape(const char* str, char* OutResult, size_t OutResultLen);

int main(void) {
    char buffer[256] = { 0 };
    const char* str = "Hello\\nworld!\\n";
    Unescape(str, buffer, strlen(str) * 2);
    printf("%s.\n", buffer);

    getchar();

    return 0;
}

int Escape(const char* str, char* OutResult, size_t OutResultLen) {
    if (!str || !OutResult || OutResultLen == 0) {
        errno = EINVAL;
        return EINVAL;
    }
    size_t i = 0; 
    size_t j = 0;
    while (str[i] != '\0' && j < OutResultLen) {
        switch (str[i]) {
            case '\a': case '\b': case '\f':
            case '\n': case '\r': case '\t':
            case '\v': case '\\':
                OutResult[j++] = '\\';
            default:
                break;
        }
        if (j >= OutResultLen) {
            break;
        }
        switch (str[i]) {
            case '\a': 
                OutResult[j] = 'a';
                break;
            case '\b': 
                OutResult[j] = 'b';
                break;
            case '\f':
                OutResult[j] = 'f';
                break;
            case '\n': 
                OutResult[j] = 'n';
                break;
            case '\r':
                OutResult[j] = 'r';
                break;
            case '\t':
                OutResult[j] = 't';
                break;
            case '\v':
                OutResult[j] = 'v';
                break;
            case '\\':
                OutResult[j] = '\\';
                break;
            default:
                OutResult[j] = str[i];
                break;                
        }
        ++i;
        ++j;
    }
    return 0;
}

int Unescape(const char* str, char* OutResult, size_t OutResultLen) {
    if (!str || !OutResult || OutResultLen == 0) {
        errno = EINVAL;
        return EINVAL;
    }
    size_t i = 0; 
    size_t j = 0;
    while (str[i] != '\0' && j < OutResultLen) {
        if (str[i] == '\\' && j < OutResultLen - 1) {
            ++i;
            switch (str[i]) {
                case 'a':
                    OutResult[j] = '\a';
                    break;
                case 'b':
                    OutResult[j] = '\b';
                    break;
                case 'f':
                    OutResult[j] = '\f';
                    break;
                case 'n':
                    OutResult[j] = '\n';
                    break;
                case 'r':
                    OutResult[j] = '\r';
                    break;
                case 't':
                    OutResult[j] = '\t';
                    break;
                case 'v':
                    OutResult[j] = '\v';
                    break;
                default:
                    OutResult[j] = str[i];
                    break;
            }
        } else {
            OutResult[j] = str[i];
        }
        ++i;
        ++j;
    }
    return 0;
}
