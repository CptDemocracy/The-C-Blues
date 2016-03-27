#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum number
 of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab. When
 either a tab or a single blank would suffice to reach a tab stop, which should be given
 preference?

 We are generally indifferent between a blank and a tab for a situation like this. However,
 for this implementation, we chose to only use spaces to achieve spacing. The reason is a 
 tab is equal to 4 spaces. Introducing extra calculation for figuring out the number of BOTH
 spaces AND tabs would unnecessarily complicate our program's logic.
*/

#define CHARS_PER_TAB_STOP 20

int main(int argc, const char** argv) {

	int count = 0;
	char c = 0;

	while (1) {
		count = 0;
		printf(">>> ");
		while ( (c = getchar()) != '\n') {
			if (c == ' ') {
				for (int i = 0; i < CHARS_PER_TAB_STOP - count; ++i) {
					putchar(' ');
				}
			}
			putchar(c);
			count = (count + 1) % CHARS_PER_TAB_STOP;
		}
		putchar('\n');
	}

	return 0;
}