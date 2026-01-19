#include "gurulib.h"
#include <stdio.h>
#include <stdlib.h>

void gerror(char* string, int code) {
	fprintf(stderr, "%s\n", string);
	exit(code);
}
