#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>

void echo(char* string) {
	printf("%s\n", string);
}

// Errors if the pointer is null
void nonull(void * pointer) {
	if (pointer == NULL) {
		fprintf(stderr, "%s", "Null pointer exception");
		exit(10);
	}
}

// Prompts the user for an integer
int prompt_int(char* print) {
	printf("%s\n", print);
	char input[32];
	fgets(input, 32, stdin);
	int result = atoi(input);
	return result;
}

// Prompts the user for a modal
int prompt_modal(char* print) {
	printf("%s (y/n)\n", print);
	char input[32];
	fgets(input, 32, stdin);

	if (input[0] == 'y') {
		return 1;
	} else {
		return 0;
	}
}

// TODO replace this with something better
int random_number(int max) {
	return random() % max;
}

// Swap two integer values in memory
void swap_ints(int *x, int *y) {

	// Dereferencing y equals the integer value stored there
	int swap = *y;

	// Get the value at y's pointer, change it to the value at x's pointer
	*y = *x;

	// Get the value at x's pointer, change it to the previous value of y's pointer
	*x = swap;
}

// Make a list of integers from 0 to limit - 1
int *make_list(int limit) {
	int* ptr = (int*) calloc(limit, sizeof(int));
	nonull(ptr);

	for (int i = 0; i < limit; ++i) {
		ptr[i] = i;
	}

	return ptr;
}

// Knuth's shuffling algorithm in C
void shuffle_list(int* list, int length) {
	for (int i = length - 1; i > 0; --i) {
		int j = random_number(i);

		// &list[j] may look scary here
		// list[j] is an integer value
		// swap_ints takes pointers, not values
		// we get the pointer from its associated value with &
		swap_ints(&list[j], &list[i]);
	}
}

int bogosort(int* list, int length) {
	if (length > 10) {
		printf("%s\n", "WARNING! This function's average big O notation is O(n*n!)");
		if (prompt_modal("Are you you you want to continue?") == 0) {
			exit(1);
		} else {
			echo("Continuing...");
		}
	}

	int success = 0;
	int steps = 0;
	while (success == 0) {
		steps++;
		shuffle_list(list, length);

		for (int i = 0; i < length - 1; ++i) {
			if (list[i] >= list[i + 1]) {
				success = 0;
				break;
			} else {
				success = 1;
			}
		}
	}

	return steps;
}

/*
Can you do
(1) A merge sort (with recursion)
(2) A quick sort (with recursion)
on arrays with sort keys such as double or strings to your liking?
Nothing is gained if you don’t know whether your programs are correct. Therefore, can you
provide a simple test routine that checks whether the resulting array really is sorted?
This test routine should just scan once through the array and should be much, much faster than
your sorting algorithms.

-------

What's quick sort?

https://en.wikipedia.org/wiki/Merge_sort

General-purpose sorting algorithm
Made in 1959 by Tony Hoare and published in 1961
Slightly faster than merge sort
Quicksort is a divide-and-conquer algorithm

1. If the current range has two or less elements, return
2. Pick a pivot point
3. Sort each element and compare it to the pivot point
	If the element is greater than the pivot, put it on the right
	If not, put it on the left
	We do not care about how MUCH greater or less than it is compared to the pivot point
4. Call the function again on each sub-range

If we had a list of 11 elements, 0 through 10...
The middle index would be... 5 with a value of 4, ideally
0 - 4  is less than 5
6 - 10 is greater than 5

[0] = 7		X
[1] = 2
[2] = 10	X
[3] = 1
[4] = 8		X
[5] = 5		X	Pivot
[6] = 11
[7] = 3		X
[8] = 4		X
[9] = 6
[10] = 9

Divide the subranges up between 0-4 and 6-10
Each subrange has an equal amount of numbers in the wrong place, 3
Swap 7 with 3, 10 with 4, and 8 with 6

*/

void quicksort(int* list, int length, int start, int end) {

	if (length <= 2) {return;}

	int pivot = (int) floor(length) / 2;

	for (int i = start; i < end; i++) {

		// If index is less than pivot and value is greater than pivot
		if (i < pivot && list[i] > pivot) {

			quicksort(list, end - start, newStart, newEnd);
		} else {

			quicksort(list, end - start, newStart, newEnd);
		}
	}
}

void print_list(int* list, int length) {
	for (int i = 0; i < length; ++i) {
		printf("%d\n", list[i]);
	}
}

int main() {
	// Seed the random number generator with the current time
	srand(time(NULL));

	int limit = prompt_int("Please input the length of the list to sort:");
	echo("");
	int* list = make_list(limit);
	shuffle_list(list, limit);

	echo("Suffled list:");
	print_list(list, limit);
	echo("------------");

	echo("Bogosorting...");
	int steps = bogosort(list, limit);
	printf("%s %d %s\n", "Sorted! Took", steps, "steps");
	print_list(list, limit);

	free(list);
}
