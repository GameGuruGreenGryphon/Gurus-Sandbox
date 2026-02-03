#include <stdint.h>

struct bit_array {
	unsigned int bit_indices;
	unsigned int array_indices;
	uint32_t* inner;
};

enum test_modes { setbit, setbitrange, getbit, getbitrange, oob };

// Handles the struct of the array
struct bit_array MakeBitArray(unsigned int bit_length);

// Returns 1 or 0
unsigned int GetBit(struct bit_array* array, unsigned int index);

// Sets a bit to 1 or 0
// Bit array increases in size when indexing beyond indices
void SetBit(struct bit_array* array, unsigned int index, unsigned int boolean);

// Returns a new bit array containing only the bits in the range
struct bit_array GetBitRange(struct bit_array* array, unsigned int index, unsigned int delta);

// Copies second array into first array starting at index
void SetBitRange(struct bit_array* changed_array, unsigned int index, struct bit_array* copied_array);

// Converts scalar values into bit arrays
struct bit_array ToBitArray(uint32_t number);

void PrintBitArray(struct bit_array* array);


void Test(struct bit_array* array, int mode);
