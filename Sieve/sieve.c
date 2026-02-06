// Sieve of Eratosthenes

#include "../BitArray/bitarray.h"

#include <stdio.h>
#include <stdlib.h>

int NextNonPrime(unsigned current, struct bit_array bits) {
	for (; GetBit(&bits, current) == 1 && current < bits.bit_indices; ++current);
	return current;
}

int main(int argc, char* argv[]) {
	if (argc == 1 || argc > 2) {
		fprintf(stderr, "Usage: sieve <limit>\n");
		exit(1);
	}

	int limit = atoi(argv[1]);

	struct bit_array primeArray = MakeBitArray(limit);

	// Go over each number in the list
	for (int i = 2; i <= limit; i = NextNonPrime(i, primeArray)) {
		printf("%d\n", i);
		// For each number in the list, filter out multiples of this number
		for (int j = i * 2; j <= limit; j = j + i) {
			SetBit(&primeArray, j, 1);
		}
	}

	// Print out primes!
	for (int i = 2; i <= limit; i++) {
		if (GetBit(&primeArray, i) == 0) {
			printf("%d\n", i);
		}
	}

	free(primeArray.inner);
}
