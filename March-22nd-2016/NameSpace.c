#include "NameSpace.h"
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <math.h>

// #define QUICK_SORT_CUTOFF_POINT 10 
// the number of items in a collection, lower than which,
// qsort will switch to insertion sort

static long lpow(long num, long power) {
	if (num == 0L) {
		return 0L;
	}
	long result = 1L;
	for (int pw = 1; pw <= power; ++pw) {
		result *= num;
	}
	return result;
}

static double dpow(double num, double power) {
	if (num == 0.0) {
		return 0.0;
	}
	int isNegativePower = power < 0.0;
	if (isNegativePower) {
		power = -power;
	}
	double result = 1.0;
	for (int pw = 1; pw <= power; ++pw) {
		result *= num;
	}
	if (isNegativePower) {
		return 1.0 / result;
	}
	return result;
}

static void quadeq(double a, double b, double c, struct PairOfDoubles* OutPair) {
	const double D = pow(b, 2.0) - 4.0 * a * c;
	if (D < 0.0) {
		errno = EDOM;
		return;
	}
	double x1 = (-b + sqrt(D)) / (2.0 * a);
	double x2 = (-b - sqrt(D)) / (2.0 * a);

	OutPair->first = x1;
	OutPair->second = x2;
}

static double gcd(double u, double v) {
	while (v > 0.0) {
		double temp = v;
		v = fmod(u, v);
		u = temp;
	}
	return u;
}

static double lcm(double u, double v) {
	return u * v / gcd(u, v);
}

static int prime(long n) {
	if (n < 2L) {
		return 0;
	}
	if (n & 1) {
		long lim = (long)sqrt(n);
		for (long div = 3L; div <= lim; ++div) {
			if ((n % div) == 0) {
				return 0;
			}
		}
		return 1;
	}
	return n == 2L;
}

static long lsum(const long* lnums, size_t len) {
	long sum = 0L;
	for (size_t i = 0u; i < len; ++i) {
		sum += lnums[i];
	}
	return sum;
}

static void gsum (const void* items, 
	size_t len, 
	size_t width, 
	void(*sum)(const void*, const void*, void* OutResult),
	void* OutResult)
{
	memcpy(OutResult, items, width);
	for (size_t i = 1u; i < len; ++i) {
		const void* pItem = (char*)items + i * width;
		sum(pItem, OutResult, OutResult);
	}
}

static void mtranspose32x32l(int rows, int cols, const long matrix[32][32], long OutResult[32][32]) 
{
	for (int row = 0; row < rows; ++row) {
		for (int col = 0; col < cols; ++col) {
			OutResult[col][row] = matrix[row][col];
		}
	}
}

static void insertionSort(void* base, size_t count, size_t width, int (*cmp)(const void*, const void*))
{
	void* buffer = calloc(1, width);

	for (size_t i = 1u; i < count; ++i) {
		for (size_t j = i; j > 0 && cmp( (char*)base + j * width, (char*)base + (j - 1) * width) < 0; --j) {
			memcpy(buffer, (char*)base + j * width, width);
			memcpy((char*)base + j * width, (char*)base + (j - 1) * width, width);
			memcpy((char*)base + (j - 1) * width, buffer, width);
		}
	}

	free(buffer);
}

static void shuffle(void* base, size_t count, size_t width, size_t seed) {
	void* buffer = calloc(1, width);
	
	srand(seed);
	for (size_t i = 0u; i < count; ++i) {
		size_t k = rand() % (i + 1);
		memcpy(buffer, (char*)base + k * width, width);
		memcpy((char*)base + k * width, (char*)base + i * width, width);
		memcpy((char*)base + i * width, buffer, width);
	}

	free(buffer);
}

static int partition(void* base, size_t lo, size_t hi, size_t width, int (*cmp)(const void*, const void*))
{
	void* buffer = calloc(1, width);

	void* pivot = (char*)base + lo * width;
	int i = lo;
	int j = hi;
	while (1) {
		while (cmp((char*)base + ++i * width, pivot) < 0) {
			if (i == hi - 1) {
				break;
			}
		}
		while (cmp((char*)base + --j * width, pivot) > 0) {
			if (j == lo) {
				break;
			}
		}
		if (i >= j) {
			break;
		}
		memcpy(buffer, (char*)base + i * width, width);
		memcpy((char*)base + i * width, (char*)base + j * width, width);
		memcpy((char*)base + j * width, buffer, width);
	}
	memcpy(buffer, pivot, width);
	memcpy(pivot, (char*)base + j * width, width);
	memcpy((char*)base + j * width, buffer, width);	

	free(buffer);
	return j;
}

static void qsortHelper(void* base, 
	size_t count, 
	size_t width, 
	size_t lo, 
	size_t hi, 
	int (*cmp)(const void*, const void*))
{
	if (hi - lo < 2) {
		return;
	}
	int mid = partition(base, lo, hi, width, cmp);
	qsortHelper(base, count, width, lo, mid, cmp);
	qsortHelper(base, count, width, mid + 1, hi, cmp);
}

static void quicksort(void* base, 
	size_t count,
	size_t width, 
	int (*cmp)(const void*, const void*))
{
	/*if (count <= QUICK_SORT_CUTOFF_POINT) {
		insertionSort(base, count, width, cmp);
	}*/
	shuffle(base, count, width, (size_t)time(NULL));
	qsortHelper(base, count, width, 0, count, cmp);
}

const struct NameSpace ns = {
	.mtranspose32x32l = mtranspose32x32l,
	.insertionSort = insertionSort,
	.quadeq = quadeq,
	.qsort = quicksort,
	.prime = prime,
	.lpow = lpow,
	.dpow = dpow,
	.gsum = gsum,
	.lsum = lsum,
	.gcd = gcd,
	.lcm = lcm,
};
