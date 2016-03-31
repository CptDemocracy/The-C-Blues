#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 256

char BUFFER[BUFFER_SIZE];

int BoyerMoore(const char* txt, const char* pat);

int main(void) {    
    
    const char* txt = "napanapanaaamapanamanaam";
    const char* pat = "manaa";
    
    int k = BoyerMoore(txt, pat);

    printf("%d\n", k);

    getchar();
    return 0;
}

int BoyerMoore(const char* txt, const char* pat) {
    int txtlen = strlen(txt);
    int patlen = strlen(pat);
    int i = 0; 
    while (i <= txtlen - patlen) {
        if (txt[i] == pat[0] && txt[i + patlen - 1] == pat[patlen - 1]) {
            int k = i + 1;
            int j = 1;
            while (j < patlen - 2) {
                if (txt[k] != pat[j]) {
                    break;
                }
                ++k, ++j;
            }
            if (j == patlen - 2) {
                return k - j;
            }
            else {
                i = k;
            }
        }
        else {
            ++i;
        }
    }
    return -1;
}
