#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct bit_array {
	unsigned int bit_indices;
	unsigned int array_indices;
	uint64_t* inner;
};

// Handles the struct of the array
struct bit_array MakeBitArray(unsigned int bit_length) {

	// Indexes are 0-based
	unsigned int bit_indices = bit_length - 1;

	// b / 64 is always truncated
	// if b = 0 - 63, b/64 = 0
	// if b = 64, b/64 = 1, but 64 bits can be stored in one element
	uint32_t to_alloc = (bit_length / 64) + ((bit_length % 64) != 0);

	// Actually allocate the memory
	uint64_t* inner = calloc(to_alloc, sizeof(uint64_t));

	// Structs!
	struct bit_array new = { bit_indices, to_alloc, inner };
	return new;
}

// Returns 1 or 0
unsigned int GetBit(struct bit_array array, unsigned int index) {

	// We don't do the fancy math from MakeBitArray() in here because this is 0-based
	int array_elem_index = index / 64;

	// Don't index bits outside of the 64 bit range
	int index_within_elem = index % 64;

	uint64_t array_elem = array.inner[array_elem_index];

	// Bit shift uint64 right until the least significant bit is the bit we want to retrieve
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
		uint64_t* new = calloc(index / 64, sizeof(uint64_t));

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
	for (unsigned int i = 0; i <= copied_array.bit_indices; i++) {
		SetBit(changed_array, i + index, GetBit(copied_array, i));
	}
}

// Converts scalar values into bit arrays
struct bit_array ToBitArray(uint64_t number) {

	uint64_t length = 0;

	while (length < 65) {
		uint64_t mask = ~0;
		mask = mask << length;

		if ( (number & ~mask) == number) {
			break;
		}

		length++;
	}

	struct bit_array new = MakeBitArray(length);

	for (unsigned int i = 0; i <= length; i++) {
		SetBit(new, i, (number >> i) & 1);
	}

	return new;
}

void PrintBitArray(struct bit_array array) {
	for (int i = array.bit_indices; i >= 0; i--) {
		printf("%d", GetBit(array, i));
	}

	printf("\n");
}

int main() {
	struct bit_array epic = MakeBitArray(64);
	PrintBitArray(epic);

	SetBit(epic, 5, 1);
	PrintBitArray(epic);

	struct bit_array awesome = ToBitArray(75);
	PrintBitArray(awesome);

	SetBitRange(epic, 0, awesome);
	free(awesome.inner);
	PrintBitArray(epic);

	free(epic.inner);
}
