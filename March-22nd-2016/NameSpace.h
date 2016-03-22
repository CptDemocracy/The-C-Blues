#ifndef NAMESPACE_H
#define NAMESPACE_H

#include <stdlib.h>

struct PairOfDoubles {
	double first;
	double second;
};

struct NameSpace {
	long (*lpow)(long n, long power);

	double (*dpow)(double n, double power);

	void	(*quadeq)(double a, double b, double c, struct PairOfDoubles* OutPair);

	double	(*gcd)(double u, double v);

	double	(*lcm)(double u, double v);

	int (*prime)(long);

	long	(*lsum)(const long* nums, size_t len);

	void	(*gsum)(const void* items, size_t len, size_t width, void(*sum)(const void*, const void*, void* OutResult), void* OutResult);

	void	(*mtranspose32x32l)(int rows, int cols, const long matrix[32][32], long OutResult[32][32]);

	void	(*qsort)(void* base, size_t count, size_t width, int (*cmp)(const void*, const void*));

	void	(*insertionSort)(void* base, size_t count, size_t width, int (*cmp)(const void*, const void*));
};

const struct NameSpace ns;

#endif /* NAMESPACE_H */
