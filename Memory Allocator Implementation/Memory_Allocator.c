#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define HEAP_SIZE 127
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

unsigned char heap[HEAP_SIZE];

void set_allocated(int header, bool allocated);
bool check_allocated(int header);
void heap_initialization();
void _malloc(int payload);
int malloc_for_realloc(int payload);
void _realloc(int pointer, int size);
void _free(int pointer);
void free_for_realloc(int pointer, int size);
void blocklist();
void writemem(int pointer, char* data);
void printmem(int pointer, int size);
void loop();

void set_allocated(int header, bool allocated)
{
    if(allocated == true)
    {
        heap[header] |= 1;  // LSB change to 1
    }
    else
    {
        heap[header] &= ~1; // LSB change to 0
    }
}

bool check_allocated(int header) //return true if header indicates allocated, otherwise false
{
    if(heap[header] & 1 == 1)   // if least significant bit is 1, then return true
    {
        return true;
    }
    else                        // else return false
    {
        return false;
    }
}

void heap_initialization()
{
    memset(heap, 0, HEAP_SIZE);
    heap[0] = HEAP_SIZE << 1;       //heap size = 127, binary in 0111 1111, after << 1, 1111 1110
    set_allocated(0, false);
}

void _malloc(int payload)
{
    //best fit, 1. loop 2. find appropriate size that is >= size 3. allocated.
    int size = payload + 1;
    int index = 0;
    int minimum_block_size = 128;
    int best_fit_index = 0;

    while(index < HEAP_SIZE) // this loop is for finding best place to malloc
    {
        if(check_allocated(index) == true) // if header indicates that the block is allocated
        {
            index = index + (heap[index] >> 1); // ex) if heap[index] = 3, then check next header which is 4, and the index of 4th place will be [3].
        }
        else // if header indecated free
        {
            char blocksize_of_char = heap[index] >> 1; // get the size of it, since char array, it is char form
            int blocksize = blocksize_of_char; // change to int

            if(blocksize < size) // if the block size is smaller than demanding size, skip
            {
                index = index + blocksize;
            }
            else
            {
                minimum_block_size = MIN(minimum_block_size, blocksize);

                if(minimum_block_size == blocksize) // need to be checked later
                {
                    best_fit_index = index;
                }

                index = index + blocksize;
            }
        }
    }

    //Assume there will be no command that request over byte size (ex only have 5 free space but request malloc(6))
    //if minimum > size, then we have to perform split

    if(minimum_block_size == size) // if it is equal
    {
        heap[best_fit_index] = minimum_block_size << 1; // minimum = size of the block, shift to the right
        set_allocated(best_fit_index, true); // set as allocated

        printf("%d\n", best_fit_index + 1);
    }
    else if (minimum_block_size == (size + 1)) // if 1 free block is expected at the end
    {
        heap[best_fit_index] = size + 1 << 1;
        set_allocated(best_fit_index, true);

        printf("%d\n", best_fit_index + 1);
    }
    else// if it is not eqaul (should only greater than size)
    {
        heap[best_fit_index] = size << 1;
        set_allocated(best_fit_index, true);

        int split_index = best_fit_index + size;
        int split_bock_size = minimum_block_size - size;

        heap[split_index] = split_bock_size << 1;
        set_allocated(split_index, false);

        printf("%d\n", best_fit_index + 1);
    }
}

int malloc_for_realloc(int payload)
{
     //best fit, 1. loop 2. find appropriate size that is >= size 3. allocated.
    int size = payload + 1;
    int index = 0;
    int minimum_block_size = 128;
    int best_fit_index = 0;

    while(index < HEAP_SIZE) // this loop is for finding best place to malloc
    {
        if(check_allocated(index) == true) // if header indicates that the block is allocated
        {
            index = index + (heap[index] >> 1); // ex) if heap[index] = 3, then check next header which is 4, and the index of 4th place will be [3].
        }
        else // if header indecated free
        {
            char blocksize_of_char = heap[index] >> 1; // get the size of it, since char array, it is char form
            int blocksize = blocksize_of_char; // change to int

            if(blocksize < size) // if the block size is smaller than demanding size, skip
            {
                index = index + blocksize;
            }
            else
            {
                minimum_block_size = MIN(minimum_block_size, blocksize);
                if(minimum_block_size == blocksize) // need to be checked later
                {
                    best_fit_index = index;
                }
                index = index + blocksize;
            }
        }
    }

    //Assume there will be no command that request over byte size (ex only have 5 free space but request malloc(6))
    //if minimum > size, then we have to perform split

    if(minimum_block_size == size) // if it is equal
    {
        heap[best_fit_index] = minimum_block_size << 1; // minimum = size of the block, shift to the right
        set_allocated(best_fit_index, true); // set as allocated

    }
    else// if it is not eqaul (should only greater than size)
    {
        heap[best_fit_index] = size << 1;
        set_allocated(best_fit_index, true);

        int split_index = best_fit_index + size;
        int split_bock_size = minimum_block_size - size;

        heap[split_index] = split_bock_size << 1;
        set_allocated(split_index, false);

    }

    return best_fit_index; // return header ptr
}

void free_for_realloc(int pointer, int size)
{
    // pointer is a ptr to the header of new free block
    // size includes the header of new free block

    for(int i = pointer + 1; i < pointer + size; i++) // delete data that is in the current payload
    {
        heap[i] = 0;
    }

    int next_header_index = pointer + size;
    int index = next_header_index;
    int total_block_size = size;

    while(check_allocated(index) == false && index < HEAP_SIZE)
    {
        int next_block_size = heap[index] >> 1;
        total_block_size = total_block_size + next_block_size;

        heap[index] = 0;

        index = index + next_block_size;
    }

    heap[pointer] = total_block_size << 1;
    set_allocated(pointer, false);
}

void _realloc(int pointer, int payload_size)
{
    // get the size of already allocated block

    int header_pointer = pointer - 1;
    char blocksize_of_char = heap[header_pointer] >> 1;
    int blocksize = blocksize_of_char; 

    if (check_allocated(header_pointer) == false)
    {
        return;
    }

    // check if blocksize is > requested size (including header)
    if (blocksize > (payload_size + 1)) 
    {
        // Case 1. current allocated payload > requested payload
        
        bool truncate = true;

        if (blocksize - (payload_size + 1) == 1)
        {
            payload_size += 1;
            truncate = false;
        }
        
        // truncate current payload
        heap[header_pointer] = (payload_size + 1) << 1;
        set_allocated(header_pointer, true);
        
        if (truncate)
        {
            int header_to_free = pointer + payload_size;            //header_to_free is split point of header
            int new_total_block_size = blocksize - (payload_size + 1);  //new_payload_size includes header

            free_for_realloc(header_to_free, new_total_block_size);
        }

        printf("%d\n", header_pointer + 1);
    }
    else if (blocksize < payload_size + 1) // if blocksize is < requested size (including header)
    {
        // Case 2. current allocated payload < request payload
        
        // check if there is a free block right after current block
        // allocate(size) | free(size)
        if (check_allocated(header_pointer + blocksize) == false)
        {
            // free block exists right after current block
            char free_block_of_char = heap[header_pointer + blocksize] >> 1;
            int free_block_size = free_block_of_char; 

            if (free_block_size > ((payload_size + 1) - blocksize)) // check if free block is enough
            {
                // Case 2-1. free space is available
                int next_free_block_header = header_pointer + blocksize;
                int exceed_range = header_pointer + payload_size + 1;

                for (int i = next_free_block_header; i < exceed_range; i++)
                {
                    heap[i] = 0;
                }

                int new_free_block_header = exceed_range;
                int new_free_block_size = free_block_size - ((payload_size + 1) - blocksize);
                heap[new_free_block_header] = (new_free_block_size) << 1;
                set_allocated(new_free_block_header, false);

                // change the size of allocated block to new size
                heap[header_pointer] = (payload_size + 1) << 1;
                set_allocated(header_pointer, true);

                printf("%d\n", header_pointer + 1);
            }
            else if(free_block_size == ((payload_size + 1) - blocksize))
            {
                int next_free_block_header = header_pointer + blocksize;
                int exceed_range = header_pointer + payload_size + 1;

                for (int i = next_free_block_header; i < exceed_range; i++)
                {
                    heap[i] = 0;
                }

                heap[header_pointer] = (payload_size + 1) << 1;
                set_allocated(header_pointer, true);

                printf("%d\n", header_pointer + 1);
            }
            else
            {
                // Case 2-2. free space is not available
                // allocate new block -> copy old block to new block -> free old block -> print ptr to payload
                // int malloc_for_realloc(); function should do malloc
                // malloc_for_realloc(); should return payload ptr
                int new_pointer = malloc_for_realloc(payload_size) + 1;
                int k = 0;
                
                // copy old to new 
                for (int i = pointer; i < pointer + blocksize; i++)
                {
                    heap[new_pointer + k] = heap[i];
                    k++;
                }

                // free old
                _free(pointer);

                // return
                printf("%d\n", new_pointer);
            }
        }
        else
        {
            // Case 2-3. free space is not available
            // allocate new block -> copy old block to new block -> free old block -> print ptr to payload
            // int malloc_for_realloc(); function should do malloc
            // malloc_for_realloc(); should return payload ptr
            int new_pointer = malloc_for_realloc(payload_size) + 1;
            int k = 0;
                
            // copy old to new 
            for (int i = pointer; i < (header_pointer + blocksize); i++)
            {
                heap[new_pointer + k] = heap[i];
                k++;
            }

            // free old
            _free(pointer);

            // return
            printf("%d\n", new_pointer);
        }
    }
}

void _free(int pointer)
{
    // delete all data that is in the payload, set free, check next header, if it is free, then combined
    int header_index = pointer - 1;

    int block_size = heap[header_index] >> 1;
    int payload_size = block_size - 1;

    for(int i = pointer; i < pointer + payload_size; i++) // delete data that is in the current payload
    {
        heap[i] = 0;
    }

    int next_header_index = header_index + block_size;
    int index = next_header_index;
    int total_block_size = block_size;

    while(check_allocated(index) == false && index < HEAP_SIZE)
    {
        int next_block_size = heap[index] >> 1;
        total_block_size = total_block_size + next_block_size;

        heap[index] = 0;

        index = index + next_block_size;
    }

    heap[header_index] = total_block_size << 1;
    set_allocated(header_index, false);
}

void blocklist()
{
    int index = 0;

    while(index < HEAP_SIZE)
    {
        if(check_allocated(index) == true) // if its is allocated
        {
            int payload_pointer = index + 1;
            int block_size = heap[index] >> 1;
            int payload_size = block_size - 1;

            printf("%d, %d, allocated\n", payload_pointer, payload_size);

            index = index + block_size;
        }
        else // if it is free
        {
            int payload_pointer = index + 1;
            int block_size = heap[index] >> 1;
            int payload_size = block_size - 1;

            printf("%d, %d, free\n", payload_pointer, payload_size);

            index = index + block_size;
        }
    }
}

void writemem(int pointer, char* data) // need to be checked that parameter is "abc", and data[0] = 'a', data[1] = 'b', data[2] = 'c'
{
    for (int i = 0; data[i] != '\0'; ++i) 
    {
        heap[pointer + i] = data[i];
    }
}

void printmem(int pointer, int size)
{
    for(int i = pointer; i < (pointer + size); i++)
    {
        if(i == (pointer + size) - 1)
        {
            printf("%X\n", heap[i]);
        }
        else
        {
            printf("%X ", heap[i]);
        }
    }
}

void loop() 
{
    char input[100];                // whole input that will be tokenized
    char input_copy[100];           // copy whole input to save original input
    char *words[100] = {NULL};      // args[0] = word, args[1] = word ...
    char *command;                  // = args[0] or First word of input
    char *arg;

    while (1) 
    {
        for(int i = 0; i < 100; i++) // initialize input each iteration to avoid null problem
        {
            input[i] = '\0';
        }

        printf("> "); // print out "> "

        
        fgets(input, sizeof(input), stdin);
        strcpy(input_copy, input); // copy input to input_copy
        arg = strtok(input, " \n\t");

        int i = 0;
        int max_index = 0;

        while (arg != NULL) // tokenize input to words,
        {
            words[i] = arg;
            max_index = i;
            i++;
            arg = strtok(NULL, " \n\t");
        }

        command = words[0]; // command = first word of input

        if (command == NULL)  // if it is just enter or nothing, then retry
        {
            continue;
        }

        if (strcmp(command, "malloc") == 0) // malloc command ex) malloc 10
        {
            if (words[1] == NULL) 
            {
                printf("Error: No size provided.\n");
            } 
            else 
            {
                int size = atoi(words[1]);
                _malloc(size);
            }
        }
        else if (strcmp(command, "realloc") == 0) // realloc command ex) realloc 1 20
        {
            if (words[1] == NULL) 
            {
                printf("Error: No size or pointer provided.\n");
            } 
            else 
            {
                int pointer = atoi(words[1]);
                int size = atoi(words[2]);
                _realloc(pointer, size);
            }
        } 
        else if (strcmp(command, "free") == 0) // free command ex) free 1
        {
            if (words[1] == NULL) 
            {
                printf("Error: No pointer provided.\n");
            } 
            else 
            {
                int pointer = atoi(words[1]);
                _free(pointer);
            }
        } 
        else if (strcmp(command, "blocklist") == 0) // blocklist command
        {
            blocklist();
        }
        else if (strcmp(command, "writemem") == 0) // writemem command ex) writemem 3 abc
        {
            if (words[1] == NULL) 
            {
                printf("Error: No pointer or data provided.\n");
            } 
            else 
            {
                int pointer = atoi(words[1]);
                writemem(pointer, words[2]);
            }
        }
        else if (strcmp(command, "printmem") == 0) // showtable command ex) printmem 3 3
        {
            if (words[1] == NULL) 
            {
                printf("Error: No pointer provided.\n");
            } 
            else 
            {
                int pointer = atoi(words[1]);
                int size = atoi(words[2]);
                printmem(pointer, size);
            }
        }
        else if (strcmp(command, "quit") == 0) // quit command
        {
            break;
        } 
    }
}

int main() {

    heap_initialization();
    loop();
    return 0;
}