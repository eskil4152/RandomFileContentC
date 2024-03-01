#include <stdio.h>
#include <stdlib.h>
#include "../include/createFile.h"
#include "../include/inputValidators/checkChoice.h"
#include "../include/createContent/createFileContentForWords.h"
#include "../include/createContent/createFileContentForWordsThreaded.h"
#include "../include/createContent/createFileContentForIntegers.h"

void createFile(){
    FILE* file;

    printf("Please provide a name for the file you want to write to \n");
    char fileName[256];

    scanf("%s", fileName);
    sprintf(fileName, "%s.txt", fileName);

    file = fopen(fileName, "w");

    int* fileContentType = checkChoice();

    switch (*fileContentType)
    {
    case 1:
        createFileContentForWords(file);
        break;
    case 2:
        createFileContentForIntegers(file);
        break;

    case 3:
        createFileContentForWordsThreaded(fileName);
        break;
    default:
        break;
    }
    
    free(fileContentType);
    fclose(file);
}
