// 0-based index and shifting functions for GetBit and SetBit

#include <stdint.h>

uint64_t GetBit(uint64_t* array, int index) {
	int array_elem_index = index / 64;
	int index_within_elem = index % 64;
	uint64_t array_elem = array[array_elem_index];
	uint64_t mask = 1;
	return (array_elem >> index_within_elem) & mask;
}

void SetBit(uint64_t* array, int index) {
	int array_elem_index = index / 64;
	int index_within_elem = index % 64;
	array[array_elem_index] |= (1 << index_within_elem);
}
