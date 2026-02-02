#include <stdio.h>

/*
argc is the number of elements passed in to the program
argc is always at least 0, as the name of the program is always passed in

argc is an array containing all the elements passed in
argc contains string elements
*/
int main(int argc, char* argv[]) {

	printf("argc: %d\n", argc);

	for (int i = 0; i < argc; i++) {
		printf("[%d]: %s\n", i, argv[i]);
	}
}
