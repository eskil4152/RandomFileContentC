#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/createContent/createFileContentForIntegers.h"
#include "../include/inputValidators/checkSizeInput.h"

void createFileContentForIntegers(FILE* file) {
    int* fileSize = checkSizeInput();
    srand(time(NULL));

    for (int i = 0; i < *fileSize; i++)
    {
        fprintf(file, "%d\r\n", rand());
    }

    printf("Successfully wrote %d numbers to file\n", *fileSize);
    
    free(fileSize);
}
