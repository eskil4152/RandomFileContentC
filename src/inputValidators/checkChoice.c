#include <stdio.h>
#include <stdlib.h>
#include "../include/inputValidators/checkChoice.h"

int* checkChoice(){
    int* input = (int*)malloc(sizeof(int));
    if (input == NULL)
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
        if (scanf("%d", input) != 1 || (*input != 1 && *input != 2 && *input != 3))
        {
            fprintf(stderr, "Invalid input, please enter \n");
            printf("1 for words \r\n");
            printf("2 for numbers \r\n");
            printf("3 for words with threads \r\n \r\n \r\n");
            while(getchar() != '\n');
        } else {
            return input;
        }
    }
}