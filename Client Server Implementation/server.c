#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char** argv) {

    if (argv[1] == NULL || strcmp (argv[1], "FIFO") == 0)
    {
        FIFO = 1; // if typed FIFO, then set FIFO as 1
    }
    else if (strcmp (argv[1], "LRU") == 0)
    {
        LRU = 1; // if typed LRU, then set LRU as 1
    }

    printf("server started/n");
    loop(); // after set FIFO and LRU, do infinite loop until typed "quit"
    return 0;
}