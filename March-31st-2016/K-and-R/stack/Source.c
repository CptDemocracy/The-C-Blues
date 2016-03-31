#include <stdio.h>
#include <ctype.h>
#include <math.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 4-4. Add the commands to print the top elements of the stack 
 without popping, to duplicate it, and to swap the top two elements. 
 Add a command to clear the stack. 
*/

#include "Stack.h"

int main(void) {
	const int COUNT = 10;
	struct Stack stack = { 0 };
	StackNew(&stack, sizeof(int), NULL);
	for (int i = 0; i < COUNT; ++i) {
		StackPush(&stack, &i);
		printf("Pushed: %d\n", i);
	}
	struct Stack stack2 = { 0 };
	StackNew(&stack2, sizeof(int), NULL);
	StackDuplicate(&stack, &stack2);
	StackSwapTopTwoElems(&stack2);
	int popped = 0;
	while (StackGetCount(&stack2) > 0) {
		StackPop(&stack2, &popped);
		printf("Popped: %d\n", popped);
	}
	StackDispose(&stack2);
	StackDispose(&stack);
	getchar();
	return 0;
}
