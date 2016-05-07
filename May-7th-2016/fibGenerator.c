#include <stdlib.h>
#include <stdio.h>

#define FIBONACCI_COUNT 40

long long FibGenerator(int reset);

/* stub program for the fibonacci number generator that fills an array 
of FIBONACCI_COUNT items (40) with fibonacci numbers and outputs the 
array contents to the screen */

int main(void)
{
    long long fibc[FIBONACCI_COUNT] = { 0 };

    for (int i = 0; i < FIBONACCI_COUNT; ++i) {
        fibc[i] = FibGenerator(0);
        printf("%lld\n", fibc[i]);
    }
    getchar();
    return EXIT_SUCCESS;
}

long long FibGenerator(int reset) 
{
    const static long long
        INIT_PREV = 0LL,
        INIT_CURR = 0LL,
        INIT_NEXT = 0LL;
    
    static long long prev, curr, next;    

    if (reset) {
        prev = INIT_PREV;
        curr = INIT_CURR;
        next = INIT_NEXT;
    }
    if (curr == INIT_CURR) {
        return curr++;
    }
    next = curr + prev;
    prev = curr;
    curr = next;
    return prev;
}
