#include <string.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
 operate on at most the first n characters of their argument strings. For example, strncpy(s,t,n) 
 copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

char* Strncpy(char* dest, const char* src, size_t count);

char* Strncat(char* dest, const char* src, size_t count);

int Strncmp(const char* s, const char* t, size_t count);

int main(void) {

    int ret = 0;
    
    const char* s = "hello";
    ret = Strncmp(s, s, strlen(s));
    printf("%d\n", ret);
    ret = strncmp(s, s, strlen(s));
    printf("%d\n", ret);

    putchar('\n');

    const char* t = "hello!";
    ret = Strncmp(s, t, strlen(t));
    printf("%d\n", ret);
    ret = strncmp(s, t, strlen(t));
    printf("%d\n", ret);

    putchar('\n');

    ret = Strncmp(s, t, strlen(s));
    printf("%d\n", ret);
    ret = strncmp(s, t, strlen(s));
    printf("%d\n", ret);

    putchar('\n');

    ret = Strncmp(t, s, strlen(t));
    printf("%d\n", ret);
    ret = strncmp(t, s, strlen(t));
    printf("%d\n", ret);

    putchar('\n');

    getchar();
    return 0;
}

char* Strncpy(char* dest, const char* src, size_t count) {
    if (!dest || !src) {
        return NULL;
    }
    while (count > 0 && *src) {
        *dest = *src;
        ++dest, ++src, --count;
    }
    *dest = 0;
    return dest;
}

char* Strncat(char* dest, const char* src, size_t count) {
    if (!dest || !src) {
        return NULL;
    }
    while (*dest) {
        ++dest;
    }
    while (count > 0 && *src) {
        *dest = *src;
        ++dest, ++src, --count;
    }
    *dest = 0;
    return dest;
}

int Strncmp(const char* s, const char* t, size_t count) {
    if (!s || !t) {
        return 0;
    }
    while (count > 0) {
        if (!*s && !*t) {
            return 0;
        }
        if (!*s) {
            return -1;
        }
        if (!*t) {
            return 1;
        }
        if (*s != *t) {
            if (*s > *t) {
                return 1;
            }
            else {
                return -1;
            }
        }
        ++s, ++t, --count;
    }
    return 0;
}
