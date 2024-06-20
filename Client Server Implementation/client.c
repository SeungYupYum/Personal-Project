#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


void quit()
{
    break;
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

        if (strcmp(command, "List") == 0) // List command
        {
            //retrieve stock name from server
        } 
        else if (strcmp(command, "Prices") == 0) // Prices command
        {
            char* file_name = words[1];
            char* date = words[2];

            //display the stock prices of stocks on a given date
        } 
        else if (strcmp(command, "MaxProfit") == 0) // MaxProfit command
        {
            char* file_name = words[1];
            //selling date must be later than the buying date
            //calculates the maximum possible profit for a single share of a given stock
        }
        else if (strcmp(command, "quit") == 0) // quit command
        {
            quit();
        } 
    }
}

int main(int argc, char** argv) {

    if (argv[1] == NULL || strcmp (argv[1], "FIFO") == 0)
    {
        FIFO = 1; // if typed FIFO, then set FIFO as 1
    }
    else if (strcmp (argv[1], "LRU") == 0)
    {
        LRU = 1; // if typed LRU, then set LRU as 1
    }

    loop(); // after set FIFO and LRU, do infinite loop until typed "quit"
    return 0;
}