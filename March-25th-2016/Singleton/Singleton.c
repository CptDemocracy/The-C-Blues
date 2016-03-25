#include <stdlib.h>
#include <stdio.h>

#include "Singleton.h"

// Singleton Pattern ([ref.] The Gang Of Four) in C
// with Lazy initialization.

static struct Singleton obj = { 0 };

static void SingletonDispose(void);

void SingletonInitialize(void) {
	// setup automatic deallocation routine on program exit
	// so that users won't have to deallocate our Singleton
	// explicitly
	obj.ptr = calloc(1, sizeof(int));
	atexit(SingletonDispose);
}

static void SingletonDispose(void) {
	free(obj.ptr);
	printf("Singleton has been disposed of.\n");
}

struct Singleton* SingletonGet(void) {
	return &obj;
}
