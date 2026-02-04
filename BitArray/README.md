# BitArray

C library for creating and managing arbitrary length bit vectors.

## Functions

`MakeBitArray(unsigned bit_length)`

Creates and allocates memory for a new struct of type bit_array.

Most other functions in this library require a bit_array pointer.

`GetBit(struct bit_array* array, unsigned index)`

Returns a 1 or a 0.

Given a bit array containing 16 bits, to get the most significant bit, pass in 15.

`SetBit(struct bit_array* array, unsigned index, unsigned boolean)`

Sets a bit at a bit index to 1 or 0.

If indexing beyond the array, `SetBit()` will allocate more memory.

Does not perform allocated memory shrinking.

`GetBitRange(struct bit_array* array, unsigned index, unsigned delta)`

Creates, allocates, and returns a new bit array containing only bits within the range.

An `index` of 2 and a `delta` of 5 will return the least significant digits from 3 through 8, inclusive.

`SetBitRange(struct bit_array* changed_array, unsigned index, struct bit_array* copied_array)`

Modifies `changed_array` to contain the same bits as `copied_array` starting at `index`.

If `copied_array` contains more bits than `changed_array` minus `index`, `changed_array` will scale to fit the bit array instead of truncating it.

`PrintBitArray(struct bit_array* array)`

Prints out the bit array.

How much it prints is determined by `array->bit_indices`, which usually represents the minimum bits required to represent the bit array.

`Test(struct bit_array* array, int mode)`

Contains unit tests for each function and feature.

These tests are kinda crummy at the moment.

`mode` = 1 - Test `SetBit()`

`mode` = 2 - Test `SetBitRange()`

`mode` = 3 - Test `SetBit()` memory reallocation

`mode` = 4 - Test `GetBit()`

`mode` = 5 - Test `GetBitRange()`

## Why?

This library helps with the Sieve project and the QR project.

I also wanted to learn how to do this sort of thing!
