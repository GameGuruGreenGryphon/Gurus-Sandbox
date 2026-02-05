# Linked List

C project for myself, for learning the linked list data structure and its applications.

## For Those Uninitiated

A linked list is a data structure. Data structures describe relationships between data.

Each element in this linked list contains only two pieces of data, a character and a pointer to the next piece of data. At each node in a linked list you can only traverse to the next node. You cannot traverse backwards through this kind of linked list.

There are other kinds of linked lists, such as one that has three pieces of data which contains the previous node, next node, and data.

### Who Cares?

Linked lists are important because they do not require contiguous memory. It does not matter WHERE these elements are stored because each element in memory knows where the next element is located. These elements can be scattered throughout the entire address space and it would not matter.

Linked lists have a benefit over C's static arrays in that it does not require reallocating the entire array when an element is added or removed.

Take for example, if an array of type int that contains 5 integers, 0 through 4. What if I wanted to add the number 5 to the end of the array? I'd need to copy this old array, make a new one with a bigger size and add the number 5, free the memory of the old array, and update the pointer to this array. That's a lot of work for adding the number 5.

For a linked list equivalent, I'd have to traverse every element until I reach an element whose next element is NULL, then update it accordingly. There's a trade-off, though. I must traverse EVERY ELEMENT until I reach the last one to append the number 5. Computers like contiguous memory more and access it faster, though, so that's a con for linked lists.
