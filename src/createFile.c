#include <stdio.h>
#include "../include/createFile.h"
#include "../include/checkChoice.h"
#include "../include/createContent/createFileContentForWords.h"
#include "../include/createContent/createFileContentForIntegers.h"

void createFile(){
    FILE* file;
    file = fopen("temp.txt", "w");

    int* fileContentType = checkChoice();

    switch (*fileContentType)
    {
    case 1:
        createFileContentForWords(file);
        break;
    case 2:
        createFileContentForIntegers(file);
        break;
    default:
        break;
    }
    
    fclose(file);
}