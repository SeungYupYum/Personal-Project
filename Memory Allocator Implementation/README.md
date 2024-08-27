# Memory Allocator

## Description

### Assumption

This is implementation of heap and memory allocator. The heap is 127 bytes long and memory is byte-addressable. The first address of the heap is address 0, so the last address of the heap is address 126. The heap will be organized as an implicit free list. The heap is initially completely unallocated, so it should contain a single free block which is as big as the entire heap. Memory is initialized so that all addresses (other than the header of the initial free block) contain 0. Each block should have a header which is a single byte and the header byte should be contained in memory, just before the payload of the block. The most-significant 7 bits of the header should indicate the size of the block, including the header itself. The least significant bit of the header should indicate the allocation of the block: 0 for free, 1 for allocated. The header for the first block (the initial single free block) must be placed at address 0 in memory.

### Operation & Features

Program provides a prompt to the user (“>”) and accept the following commands.

- **malloc**: This operation allows the user to allocate a block of memory from the heap. This operation should take one argument, the number of bytes which the user wants in the payload of the allocated block. This operation should print out a pointer which is the first address of the payload of the allocated block. For example,
  ```cpp
  > malloc 10
  1
  > malloc 5
  12
  > malloc 2
  18

- **realloc**: This operation allows the user to resize a previously allocated block of memory. The operation takes two arguments. The first argument is a pointer to the payload of a previously allocated block of memory, and the second argument is the new size in bytes that the user wants for the payload of that block. If the new size is smaller than the current size of the block, program should truncate the block and free any excess memory. If the new size is larger and there is sufficient adjacent free space in the heap, program should expand the block into the adjacent free space. If there is not enough adjacent free space, program should allocate a new block of the appropriate size, copy the contents of the old block to the new block, free the old block, and return a pointer to the payload of the new block.
  ```cpp
  > malloc 10
  1
  > realloc 1 20
  1
  > realloc 1 5
  1

- **free**: This operation allows the user to free a block of memory. This operation takes one argument, the pointer to the payload of a previously allocated block of memory.
  ```cpp
  > malloc 10
  1
  > malloc 5
  12
  > free 12
  > free 1

- **blocklist**: This operation prints out information about all of the blocks in the heap. The information about blocks should be printed in the order that the blocks are contained in the heap. The following information should be printed about each block: pointer to the payload, block size, and the allocation status (allocated of free). All three items of information about a single block should be printed on a single line and should be separated by commas.
  ```cpp
  > malloc 10
  1
  > malloc 5
  12
  > blocklist
  1, 10, allocated
  12, 5, allocated
  18, 109, free

- **writemem**: This operation writes alpha-numeric characters into memory. The operation takes two arguments and there should be no empty spaces or null character at the end of the input. The first argument is a pointer to the location in memory and the second argument is a sequence of alpha-numeric characters which will be written into memory, starting at the address indicated by the pointer. The first character will be written into the address indicated by the pointer, and each character thereafter will be written into the neighboring addresses sequentially. For example, the operation “writemem 3 abc” will write an ‘a’ into address 3, a ‘b’ into address ‘4’, and a ‘c’ into address 5.

- **printmem**: This operation prints out a segment of memory in hexadecimal. The operation takes two arguments. The first argument is a pointer to the first location in memory to print, and the second argument is an integer indicating how many addresses to print. The contents of all addresses will be printed on a single line and separated by a single space.

  ```cpp
  > writemem 5 ABC
  > printmem 5 3
  41 42 43
  The values 41, 42, and 43 are the hexadecimal representations of the ASCII values of the characters ‘A’, ‘B’, and ‘C’.

- **quit**: This quits the program.


