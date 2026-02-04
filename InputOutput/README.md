# InputOutput

C project for myself, for learning the IO systems provided by C.

## For Those Uninitiated

The compiled C executable of this program takes any and all arguments given to it in the command line.

These are stored in the second parameter of `main()` conventionally called `argv` for argument vector.

The first parameter of `main()` is an integer containing the number of elements in `argv`. By convention, this is called `argc`, for argument count.


`argv` is an array of char pointers. `argv[0]` returns a value of `*char`, pointing to the first character of the first element.

`argv[0]` is the executable's name by standard.

Because of this, `argc` is always greater than 0.


`printf()` prints formatted text to standard output.

`printf()` takes at least one argument, the first one being the format specifier.

A format specifier looks something like `"%d"`. Most characters can go between the quotes, but the % indicates something special.

`%d` specifies the second argument passed in to `printf()` is a number.

Calling `printf("%d", number)` will print the value contained in `number` if it is an integer.

Calling `printf("%d %d %d", num1, num2, num3)` will print the values contained in `num1`, `num2`, and `num3` if they are integers.


You can put more than just format specifiers in `printf()`, though.

Calling `printf("Number passed in: %d", number`) will print `"Number passed in: 10"` if `number` is 10.
