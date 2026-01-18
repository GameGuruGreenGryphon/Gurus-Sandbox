#include "gurulib.h"
#include <stdio.h>
#include <stdlib.h>

void gError(char* string, int code) {
	fprintf(stderr, "%s\n", string);
	exit(code);
}
