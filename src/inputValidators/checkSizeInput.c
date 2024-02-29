#include <stdio.h>
#include <stdlib.h>
#include "../include/inputValidators/checkSizeInput.h"

int* checkSizeInput() {
    int* input = (int*)malloc(sizeof(int));
    if (input == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    printf("Please enter size: \n");
    while (1) {
        if (scanf("%d", input) != 1 || *input < 1) {
            fprintf(stderr, "Invalid input, please enter a number \n");
            while(getchar() != '\n');
        } else {
            return input;
        }
    }
}