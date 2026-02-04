# Memory

C project for myself, for learning how to use `malloc()`.

## For Those Uninitiated

`malloc()` is a function to allocate memory.

It allocates `n` bytes of memory on the heap.

This memory should be cleared before the end of the program. C does not do this for you, so you must do it yourself. Failing to do this in a timely manner will make the program use more memory than it needs, and at worst, causes a memory leak.

`free()` frees memory allocated by `malloc()` and other related functions.
