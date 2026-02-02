// Sieve of Eratosthenes

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

uint64_t Index64(uint64_t* array, int index) {
	uint64_t value = array[index - 1 / 64];
	return value;
}

// bit is 1 through 64 * array size
// returns 0 if bit is 0, nonzero if bit is 1
uint64_t GetBit(uint64_t* array, int bit) {
	/*
	Some napkin bit operations
	If the array only had 00101001 stored...
	And you wanted to check the first bit...
	You'd check the least significant bit
	00101001	Bit array
	00000001	Bitwise AND
	00000001	Bit 1 is true, so returns true

	00101000	Bit array
	00000001	Bitwise AND
	00000000	Bit 1 is false, so returns false

	If you want the 64th bit, bit is 64 and bit-1/64 = 0
	If you want the 65th bit, bit wraps around to 1 again and bit-1/64 = 1
	*/

	// Gets the n-1 bit of an array
	// Because this is integer division, this automatically floors it, which is what we want

	// Bitwise & to check if it's 1 or 0
	// Bit shift properly to check the correct bit

	uint64_t shift = 1 << ( (bit % 64) - 1);

	uint64_t r = Index64(array, bit) & shift;

	return r;
}

void SetBit(uint64_t* array, int bit, int bool) {

	/*
	If we wanted to set the 2nd bit to 0...

	00110010
	11111101	Bitwise AND
	00110000

	How the hell do we get that number?
	We flip the bits of the number 2 for the mask

	If we wanted to set the third bit to 1...
	
	00110010
	00000100	Bitwise OR
	00110110
	*/
	if (bool) {
		// Bitwise OR with normal bit index
		array[bit - 1 / 64] |= 1 << ((bit % 64) - 1);
	} else {
		// Bitwise AND with one's compliment of bit index
		array[bit - 1 / 64] &= ~(1 << ((bit % 64) - 1));
	}
}

int main() {
	uint64_t limit;
	printf("%s\n", "Please enter an integer:");
	limit = 100;
	// scanf("%lu", &limit);
	/*
	This is a bit array, storing bit values
	We need this to store whether or not a number is prime
	Each index has 64 bits to it
	Index bits 1 through 64 of sieve[0] for the first 64 boolean values
	Index bits 1 through 64 of sieve[1] for the 65 - 128 boolean values, and so on
	This is effectively a * 64 index saving measure
	*/

	void * primeArray = calloc( ceilf(limit / 64.0), sizeof(uint64_t));

	// Go over each number in the list
	uint64_t i;
	for (i = 2; i <= limit; i++) {

		uint64_t j;
		// For each number in the list, filter out multiples of this number
		for (j = i * 2; j <= limit; j = j + i) {
			// Check if number is not marked as prime
			if (GetBit(primeArray, j) == 0) {
				SetBit(primeArray, j, 1);
			}
		}
	}

	// Print out primes!
	for (i = 2; i <= limit; i++) {
		if (GetBit(primeArray, i) == 0) {
			printf("%lu\n", i);
		}
	}

	free(primeArray);
}
