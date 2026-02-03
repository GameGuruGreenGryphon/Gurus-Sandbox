#include "bitarray.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int count = 0;
void debug(char* string) {
	printf("[%d]: %s\n", ++count, string);
}

// Handles the struct of the array
struct bit_array MakeBitArray(unsigned int bit_length) {

	// Indexes are 0-based
	unsigned int bit_indices = bit_length - 1;

	// b / 32 is always truncated
	// if b = 0 - 63, b/32 = 0
	// if b = 32, b/32 = 1, but 32 bits can be stored in one element
	uint32_t to_alloc = (bit_length / 32) + ((bit_length % 32) != 0);

	// Actually allocate the memory
	uint32_t* inner = calloc(to_alloc, sizeof(uint32_t));

	// Structs!
	struct bit_array new = { bit_indices, to_alloc, inner };
	return new;
}

// Returns 1 or 0
unsigned int GetBit(struct bit_array* array, unsigned int index) {

	// We don't do the fancy math from MakeBitArray() in here because this is 0-based
	int array_elem_index = index / 32;

	// Don't index bits outside of the 32 bit range
	int index_within_elem = index % 32;

	uint32_t array_elem = array -> inner[array_elem_index];

	// Bit shift uint32 right until the least significant bit is the bit we want to retrieve
	uint32_t mask = 1;
	return (array_elem >> index_within_elem) & mask;
}

// Sets a bit to 1 or 0
// Bit array increases in size when indexing beyond indices
void SetBit(struct bit_array* array, unsigned int index, unsigned int bool) {

	// Increase bit length if setting bit outside of bit length, but within allocated memory
	// i.e. array of 32 bits with bit length 24, setting 32 to 1 would adjust accordingly
	if (index > array -> bit_indices) {
		array -> bit_indices = index;
	}

	// Increase array length if setting bit outside of allocated memory
	if (index >= ((array -> array_indices) * 32)) {
		int bit_length = index + 1;
		uint32_t to_alloc = (bit_length / 32) + ((bit_length % 32) != 0);

		// Increase size of array
		array -> inner = reallocarray(array -> inner, to_alloc, sizeof(uint32_t));

		// Fill in new memory with zeros
		for (unsigned int i = array->array_indices; i < to_alloc; i++) {
			array->inner[i] = (uint32_t) 0;
		}

		array -> array_indices = to_alloc;
	}


	int array_elem_index = index / 32;
	int index_within_elem = index % 32;

	if (bool) {
		array -> inner[array_elem_index] |= (1 << index_within_elem);
	} else {
		array -> inner[array_elem_index] &= ~(1 << index_within_elem);
	}

}

// Returns a new bit array containing only the bits in the range
struct bit_array GetBitRange(struct bit_array* array, unsigned int index, unsigned int delta) {
	struct bit_array new = MakeBitArray(delta);

	for (unsigned int i = 0; i <= delta; i++) {
		SetBit(&new, i, GetBit(array, i + index));
	}

	return new;
}

// Copies second array into first array starting at index
void SetBitRange(struct bit_array* changed_array, unsigned int index, struct bit_array* copied_array) {
	for (unsigned int i = 0; i <= copied_array -> bit_indices; i++) {
		SetBit(changed_array, i + index, GetBit(copied_array, i));
	}
}

// Converts scalar values into bit arrays
struct bit_array ToBitArray(uint32_t number) {

	uint32_t length = 0;

	while (length < 65) {
		uint32_t mask = ~0;
		mask = mask << length;

		if ( (number & ~mask) == number) {
			break;
		}

		length++;
	}

	struct bit_array new = MakeBitArray(length);

	for (unsigned int i = 0; i < length; i++) {
		SetBit(&new, i, (number >> i) & 1);
	}

	return new;
}

void PrintBitArray(struct bit_array* array) {
	for (int i = array -> bit_indices; i >= 0; i--) {
		printf("%d", GetBit(array, i));
	}

	printf("\n");
}

void Test(struct bit_array* array, int mode) {
	switch(mode) {
		case 1:
			// Test setbit
			SetBit(array, 5, 1);
			printf("Set sixth bit to 1\n");
			PrintBitArray(array);
			break;
		case 2:
			// Test setbitrange
			printf("75 in bit form\n");
			struct bit_array awesome = ToBitArray(75);
			PrintBitArray(&awesome);

			printf("Set bits in first bit array to 75 bit string\n");
			SetBitRange(array, 0, &awesome);
			free(awesome.inner);
			PrintBitArray(array);
			break;
		case 3:
			// Test setbit when out of bounds
			SetBit(array, array->bit_indices + 10, 1);
			printf("Set bit 10 bit indices past max bit length\n");
			PrintBitArray(array);
			break;
		case 4:
			// Test getbit
			printf("Fifth bit\n");
			printf("%d\n", GetBit(array, 5));
			printf("Sixth bit\n");
			printf("%d\n", GetBit(array, 6));
			break;
		case 5:
			// Test getbitrange
			printf("Bit index 0 through 5\n");
			struct bit_array range = GetBitRange(array, 0, 5);
			PrintBitArray(&range);
			free(range.inner);
	}
}

int main(int argc, char* argv[]) {
	printf("args: %d\n", argc);
	int number = atoi(argv[1]);
	printf("input: %d\n", number);

	struct bit_array epic = MakeBitArray(number);
	printf("New bit array\n");
	PrintBitArray(&epic);
	printf("\n");

	Test(&epic, 3);

	free(epic.inner);
}
