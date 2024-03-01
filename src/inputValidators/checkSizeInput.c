#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/inputValidators/checkSizeInput.h"

int* checkSizeInput() {
    char input[256];
    int* choice = (int*)malloc(sizeof(int));

    if (choice == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    printf("Please enter size: \n");
    while (1) {
        fflush(stdout);

        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (atoi(input) != 0)
        {
            *choice = atoi(input);

            if (*choice >= 1)
            {
                return choice;
            } else {
                printf("Invalid input. Enter a number greater than 0. \n");
            }
        } else {
            printf("Invalid input. Enter a valid number. \n");
        }
    }
}
