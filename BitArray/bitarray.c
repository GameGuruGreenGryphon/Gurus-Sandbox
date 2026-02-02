#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct bit_array {
	unsigned int bit_indices;
	unsigned int array_indices;
	uint64_t* inner;
};

// CALLOC!!!!
uint64_t* AllocateArray(unsigned int bit_length) {
	unsigned int size = bit_length / 64;
	uint64_t* new = calloc(size, sizeof(uint64_t));
	return new;
}

// Handles the struct of the array
struct bit_array MakeBitArray(unsigned int bit_length) {
	unsigned int bit_indices = bit_length - 1;
	unsigned int array_indices = bit_length / 64;
	uint64_t* inner = AllocateArray(bit_length);

	struct bit_array new = { bit_indices, array_indices, inner };
	return new;
}

// Returns 1 or 0
unsigned int GetBit(struct bit_array array, unsigned int index) {
	int array_elem_index = index / 64;
	int index_within_elem = index % 64;
	uint64_t array_elem = array.inner[array_elem_index];
	uint64_t mask = 1;
	return (array_elem >> index_within_elem) & mask;
}

// Sets a bit to 1 or 0
void SetBit(struct bit_array array, unsigned int index, unsigned int bool) {

	if (index > array.bit_indices) {
		array.bit_indices = index;
	}

	// If index is beyond actual allocated memory
	if (index > ( (array.array_indices + 1) * 64)) {

		// downloadmoreram.com
		uint64_t* new = AllocateArray(index);

		// Copy data to new memory location
		for (unsigned int i = 0; i <= array.array_indices; i++) {
			new[i] = array.inner[i];
		}

		// Free old, crappy memory
		free(array.inner);

		// Does this actually work?
		array.inner = new;
	}

	int array_elem_index = index / 64;
	int index_within_elem = index % 64;

	if (bool) {
		array.inner[array_elem_index] |= (1 << index_within_elem);
	} else {
		array.inner[array_elem_index] &= ~(1 << index_within_elem);
	}

}

// Returns a new bit array containing only the bits in the range
struct bit_array GetBitRange(struct bit_array array, unsigned int index, unsigned int delta) {
	struct bit_array new = MakeBitArray(delta);

	for (unsigned int i = 0; i <= delta; i++) {
		SetBit(new, i, GetBit(array, i + index));
	}

	return new;
}

// Copies second array into first array starting at index
void SetBitRange(struct bit_array changed_array, unsigned int index, struct bit_array copied_array) {
	for (unsigned int i = 0; i < copied_array.bit_indices; i++) {
		SetBit(changed_array, i + index, GetBit(copied_array, i));
	}
}

void PrintBitArray(struct bit_array array) {
	for (unsigned int i = 0; i <= array.bit_indices; i++) {
		if (GetBit(array, i)) {
			printf("%c", '1');
		} else {
			printf("%c", '0');
		}
	}
	printf("\n");
}

int main() {
	struct bit_array epic = MakeBitArray(100);
	PrintBitArray(epic);

	SetBit(epic, 5, 1);
	PrintBitArray(epic);
}
