/*
* Generic sum function:
*
* base - pointer to the base of the collection to be evaluated
* itemCount - the number of items in the collection to be summed
* itemSize - the number in bytes of the type of object stored in the collection
* binarySumFunc - pointer to a function used to add two items together and return result in the memory pointed to by "OutResult"
* OutResult - pointer to the memory where the result of evaluation should be stored
*/
int Sum(const void* base, 
	size_t itemCount, 
	size_t itemSize,
	void (*binarySumFunc)(const void* a, const void* b, void* OutResult),
	void* OutResult)
{
	if (!base || itemSize < 1 || !binarySumFunc || !OutResult) {
		errno = EINVAL;
		return EINVAL;
	}
	memset(OutResult, 0, itemSize);
	if (itemCount < 1) {
		return 0;
	}
	else if (itemCount == 1) {
		memcpy(OutResult, base, itemSize);
		return 0;
	}
	memcpy(OutResult, base, itemSize);
	for (size_t i = 1; i < itemCount; ++i) {
		binarySumFunc(OutResult, (char*)base + i * itemSize, OutResult);
	}
	return 0;
}
