#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 256

char BUFFER[BUFFER_SIZE];

int BoyerMoore(const char* txt, const char* pat);

int main(void) {    
    
    const char* txt = "naanaaanaam";
    const char* pat = "naam";
    
    int k = BoyerMoore(txt, pat);

    printf("%d\n", k);

    getchar();
    return 0;
}

int BoyerMoore(const char* txt, const char* pat) {
    size_t txtlen = strlen(txt);
    size_t patlen = strlen(pat);
    size_t i = 0; 
    while (i <= txtlen - patlen) {
        if (txt[i] == pat[0] && txt[i + patlen - 1] == pat[patlen - 1]) {
            size_t k = i + 1;
            size_t j = 1;
            while (j < patlen - 2) {
                if (txt[k] != pat[j]) {
                    break;
                }
                ++k, ++j;
            }
            if (j == patlen - 2) {
                return k - j;
            }
        }
        else {
            ++i;
        }
    }
    return -1;
}
