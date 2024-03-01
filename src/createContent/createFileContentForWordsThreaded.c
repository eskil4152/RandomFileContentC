#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>
#include "../include/createContent/createFileContentForWordsThreaded.h"
#include "../include/inputValidators/checkSizeInput.h"

void* myThread(void* args){
    void** argsP = (void**)args;

    FILE* fileRead = fopen("words.txt", "r");
    FILE* fileWrite = (FILE*)argsP[0];
    int lines = *((int*)argsP[1]);
    int numbers = *((int*)argsP[2]);

    for (int i = 0; i < numbers; i++)
    {
        char line[64];
        int currentLine = 0;
        int random = (rand() % (lines - 0 + 1)) + 0;

        fseek(fileRead, 0, SEEK_SET);

        while (fgets(line, 1024, fileRead) != NULL) {
            currentLine++;
            if (currentLine == random) {
                fprintf(fileWrite, "%s", line);
                break;
            }
        }   
    }

    printf("Done \n");

    return NULL;
}

void createFileContentForWordsThreaded(char* fileName){
    FILE* fileRead = fopen("words.txt", "r");

    FILE* file = fopen(fileName, "w+");
    fclose(file);

    FILE* fileWrite = fopen(fileName, "a");

    int threads = 4;
    pthread_t thread[threads];

    int* input;
    int lines = 0;
    int c;

    for (c = getc(fileRead); c != EOF; c = getc(fileRead)) {
        if (c == '\n')
        {
            lines++;
        }
    }

    fseek(fileRead, 0, SEEK_SET);

    while (1)
    {
        input = checkSizeInput();

        if (*input <= lines)
        {
            break;
        }
        
        printf("Input must not be greater than %d\n", lines);
    }

    fclose(fileRead);

    int numberToPrint = *input;
    int numbersPerThread = numberToPrint / threads;
    printf("Numbers pr: %d\n", numbersPerThread);

    void* args[3];
    args[0] = (void*)fileWrite;
    args[1] = (void*)&lines;
    args[2] = (void*)&numbersPerThread;

    for (int i = 0; i != threads; i++)
    {
        pthread_create(&thread[i], NULL, myThread, (void*)args); 
    }

    for (int i = 0; i < threads; i++)
    {
        pthread_join(thread[i], NULL); 
    }  

    exit(0); 
}