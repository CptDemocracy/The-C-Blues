#include <string.h>
#include <stdio.h>

#define SWAP(type, x, y) \
    do { type temp = x; x = y; y = temp; } while (0)

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 4-14. Define a macro swap(t,x,y) that interchanges 
 two arguments of type t. (Block structure will help.)
*/

int main(void) {

    const char* OUTPUT_FORMAT = "x = %d, y = %d\n";
    int x = 1, y = 2;
    printf(OUTPUT_FORMAT, x, y);
    SWAP(int, x, y);
    printf(OUTPUT_FORMAT, x, y);        

    getchar();
    return 0;
}
