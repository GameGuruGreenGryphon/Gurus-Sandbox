# Compile

C Project for learning how to compile source files and libraries together into one executable.

## For Those Uninitiated

This directory contains four main files.

`compile.c` - Contains `main()` and has `#include "gurulib.c"`.

`gurulib.c` - Contains function definitions for functions declared in `gurulib.h`.

`gurulib.h` - Contains function declarations.

`build.sh` - Runs `gcc` to compile `gurulib.c` into `gurulib.o`, then compiles `compile.c` and `compile.o` into binary executable `compiled`.
