#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inputValidators/checkChoice.h"

int* checkChoice(){
    char input[256];
    int* choice = (int*)malloc(sizeof(int));

    if (choice == NULL)
    {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    printf("Please enter: \n");
    printf("1 for words \n");
    printf("2 for numbers \n");
    printf("3 for words with threads\n");
    while (1)
    {
        fflush(stdout);

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (atoi(input) != 0)
        {
            *choice = atoi(input);

            if (*choice >= 1 && *choice <= 3)
            {
                return choice;
            } else {
                printf("Invalid input. Enter a number between 1 and 3. \n");
            }
        } else {
            printf("Invalid input. Enter a valid number. \n");
        }
    }
}