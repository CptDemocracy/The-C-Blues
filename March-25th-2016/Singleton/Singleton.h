#ifndef SINGLETON_H
#define SINGLETON_H

// Singleton Pattern ([ref.] The Gang Of Four) in C
// with Lazy initialization.

struct Singleton {
	int* ptr;
};

void SingletonInitialize(void);

struct Singleton* SingletonGet(void);

#endif /* SINGLETON_H */
