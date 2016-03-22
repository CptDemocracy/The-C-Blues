#include "Vector.h"
#include <string.h>

#define DEFAULT_VECTOR_CAPACITY		4
#define VECTOR_CAPACITY_MULTIPLIER	2

static int VectorEnsureCapacity(struct Vector*, size_t minCapacity);

int VectorNew(struct Vector* self, size_t itemSize, int (*DisposeFn)(void*)) {
	if (!self) {
		errno = EINVAL;
		return errno;
	}

	self->_itemSize  = itemSize;
	self->_capacity  = DEFAULT_VECTOR_CAPACITY;
	self->_itemCount = 0;
	self->DisposeFn  = DisposeFn;

	self->_items = calloc(self->_capacity, itemSize);
	if (!self->_items) {
		free(self);
		errno = ENOMEM;
		return errno;
	}
	return 0;
}

int VectorDispose(struct Vector* self) {
	if (!self) {
		errno = EINVAL;
		return errno;
	}
	
	if (self->DisposeFn) {
		size_t count = self->_itemCount;
		size_t itemSize = self->_itemSize;
		for (size_t i = 0; i < count; ++i) {
			void* item = (char*)self->_items + i * itemSize;
			self->DisposeFn(item);
		}
	}
	free(self->_items);

	return 0;
}

int VectorAdd(struct Vector* self, void* item) {
	if (!self || !item) {
		errno = EINVAL;
		return errno;
	}
	errno = VectorEnsureCapacity(self, self->_itemCount + 1);
	if (errno) {
		return errno;
	}
	void* target = (char*)self->_items + self->_itemSize * self->_itemCount;
	memcpy(target, item, self->_itemSize);
	++self->_itemCount;
	return 0;
}

size_t VectorGetCount(struct Vector* self) {
	if (!self) {
		errno = EINVAL;
		return errno;
	}
	return self->_itemCount;
}

int VectorGet(struct Vector* self, size_t index, void* OutResult) {
	if (!self) {
		errno = EINVAL;
		return EINVAL;
	}
	if (index >= self->_itemCount) {
		errno = EINVAL;
		return EINVAL;
	}
	memcpy(OutResult, (char*)self->_items + index * self->_itemSize, self->_itemSize);
	return 0;
}

int VectorSet(struct Vector* self, size_t index, void* item) {
	if (!self || !item) {
		errno = EINVAL;
		return errno;
	}
	if (index >= self->_itemCount) {
		errno = EINVAL;
		return errno;
	}
	void* target = (char*)self->_items + index * self->_itemSize;
	memcpy(target, item, self->_itemSize);
	return 0;
}

static int VectorEnsureCapacity(struct Vector* self, size_t minCapacity) {
	if (!self) {
		errno = EINVAL;
		return errno;
	}
	if (self->_capacity < minCapacity) {
		size_t newCapacity = self->_capacity * VECTOR_CAPACITY_MULTIPLIER > minCapacity ? 
											self->_capacity * VECTOR_CAPACITY_MULTIPLIER : minCapacity;
		void* newArray = calloc(newCapacity, self->_itemSize);
		if (!newArray) {
			errno = ENOMEM;
			return errno;
		}
		memcpy(newArray, self->_items, self->_itemCount * self->_itemSize);

		// it is important that we do NOT run DisposeFn on the items at
		// this point
		free(self->_items);

		self->_capacity = newCapacity;
		self->_items = newArray;
	}
	return 0;
} 
