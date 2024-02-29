#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/createContent/createFileContentForIntegers.h"
#include "../include/checkSizeInput.h"

void createFileContentForIntegers(FILE* file) {
    int* fileSizeP = checkSizeInput();
    int fileSize = *fileSizeP;
    srand(time(NULL));

    for (int i = 0; i < fileSize; i++)
    {
        fprintf(file, "%d\r\n", rand());
    }
}