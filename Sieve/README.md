# Sieve

Sieve of Eratosthenes implementation.

Contains my first implementation of a bit vector!

## For Those Uninitiated

Primes are any integer that can only divide by itself and 1 to result in an integer.

The Sieve of Eratosthenes is an algorithm of finding all primes at and below an input `n`.

It keeps track of primes with a table of boolean values.

For each integer below `n` marked as prime, defined as `i`, each multiple of `i` past itself is marked as not prime.
