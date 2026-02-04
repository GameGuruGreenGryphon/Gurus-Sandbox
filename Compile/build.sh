#!/bin/env bash

gcc -c "gurulib.c" -o "gurulib.o"
wait
gcc "compile.c" -Wall -Wextra -fsanitize=address -o "compiled" "gurulib.o"
