#!/bin/env bash

gcc -c "../BitArray/bitarray.c" -o "bitarray.o"
wait
gcc "qr.c" "bitarray.o" -Wall -Wextra -fsanitize=address -o "qr"
