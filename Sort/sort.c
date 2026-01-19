#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

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
