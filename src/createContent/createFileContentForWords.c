#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "../include/tools/cJSON.h"
#include "../include/createContent/createFileContentForWords.h"
#include "../include/inputValidators/checkSizeInput.h"

#define MAX_LINE_LENGTH 1024

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

void createFileContentForWords(FILE* file){
    FILE* readFile = fopen("words.txt", "r");
    if (!readFile)
    {
        printf("no read file\n");
        return;
    }
    
    int lines = 0;
    int c;

    for (c = getc(readFile); c != EOF; c = getc(readFile)) {
        if (c == '\n')
        {
            lines++;
        }
    }

    fseek(readFile, 0, SEEK_SET);
    int* input;

    while (1)
    {
        input = checkSizeInput();

        if (*input <= lines)
        {
            break;
        }
        
        printf("Input must not be greater than %d\n", lines);
    }

    for (int i = 0; i < *input; i++)
    {
        char line[MAX_LINE_LENGTH];
        int currentLine = 0;
        int random = (rand() % (lines - 0 + 1)) + 0;

        fseek(readFile, 0, SEEK_SET);

        while (fgets(line, MAX_LINE_LENGTH, readFile) != NULL) {
            currentLine++;
            if (currentLine == random) {
                fprintf(file, "%s", line);
                break;
            }
        }
    }
    free(input);
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    char *response_buffer = (char *)userdata;

    memcpy(response_buffer, ptr, total_size);

    return total_size;
}
