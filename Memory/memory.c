#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	// Make a new array of size 8, populate it with elements of index * 128
	int size = 8;
	int* array = malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++) {
		array[i] = i * 128;
	}

	for (int i = 0; i < size; i++) {
		printf("[%d]: %d\n", i, array[i]);
	}

	printf("\n");

	// Reuse old data, append new data to it
	int oldsize = size;
	size = 16;

	// Pointer, bytes, elements
	// Returns the new pointer, automatically frees old pointer
	array = reallocarray(array, sizeof(int) * size, size);

	for (int i = oldsize; i < size; i++) {
		array[i] = i * 128;
	}

	for (int i = 0; i < size; i++) {
		printf("[%d]: %d\n", i, array[i]);
	}

	free(array);
}
