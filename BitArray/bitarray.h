#include <stdint.h>

struct bit_array {
	unsigned int bit_indices;
	unsigned int array_indices;
	uint32_t* inner;
};

enum test_modes { setbit, setbitrange, getbit, getbitrange, oob };

struct bit_array MakeBitArray(unsigned int bit_length);

unsigned int GetBit(struct bit_array* array, unsigned int index);

void SetBit(struct bit_array* array, unsigned int index, unsigned int boolean);

struct bit_array GetBitRange(struct bit_array* array, unsigned int index, unsigned int delta);

void SetBitRange(struct bit_array* changed_array, unsigned int index, struct bit_array* copied_array);

struct bit_array ToBitArray(uint32_t number);

void PrintBitArray(struct bit_array* array);

void Test(struct bit_array* array, int mode);
