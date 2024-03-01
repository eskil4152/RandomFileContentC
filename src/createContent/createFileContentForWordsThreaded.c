#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "../include/createContent/createFileContentForWordsThreaded.h"
#include "../include/inputValidators/checkSizeInput.h"

#define MAX_LINE_LENGTH 1024
#define BUFFER_SIZE 1000

char buffer[BUFFER_SIZE][MAX_LINE_LENGTH];
int bufferIndex = 0;
int bufferCount = 0;
int linesRead = 0; // Tracks the total lines read by reader threads

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t canRead = PTHREAD_COND_INITIALIZER;
pthread_cond_t canWrite = PTHREAD_COND_INITIALIZER;
int endOfFile = 0; // Flag to indicate end of file

void* reader(void* arg) {
    FILE* file = (FILE*)arg;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        pthread_mutex_lock(&mutex);
        while (bufferCount >= BUFFER_SIZE) {
            pthread_cond_wait(&canWrite, &mutex);
        }
        
        strcpy(buffer[bufferIndex], line);
        bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
        bufferCount++;
        pthread_cond_signal(&canRead);
        pthread_mutex_unlock(&mutex);
        linesRead++;
    }

    // Set endOfFile flag when reader threads finish
    endOfFile = 1;

    pthread_exit(NULL);
}

void* writer(void* args) {
    void** arg_array = (void**)args;
    FILE* file = (FILE*)arg_array[0];
    int totalLines = *((int*)arg_array[1]);

    while (1) {
        pthread_mutex_lock(&mutex);
        while (bufferCount <= 0 && !endOfFile) {
            pthread_cond_wait(&canRead, &mutex);
        }

        if (bufferCount <= 0 && endOfFile) {
            pthread_mutex_unlock(&mutex);
            break;
        }

        fprintf(file, "%s", buffer[bufferIndex]);
        bufferIndex = (bufferIndex + 1) % BUFFER_SIZE;
        bufferCount--;
        pthread_cond_signal(&canWrite);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void createFileContentForWordsThreaded(FILE* file){
    FILE* readFile = fopen("words.txt", "r");
    if (!readFile)
    {
        printf("no file");
        return;
    }

    int lines = 0;
    int c;

    for (c = getc(readFile); c != EOF; c = getc(readFile)) {
        if (c == '\n') {
            lines++;
        }
    }

    fseek(readFile, 0, SEEK_SET);
    int* input;

    while (1) {
        input = checkSizeInput();

        if (*input <= lines) {
            break;
        }
        
        printf("Input must not be greater than %d\n", lines);
    }

    // Pass totalLines and file pointer to writer threads
    void* args[2];
    args[0] = (void*)file;
    args[1] = (void*)&lines;

    // Initialize reader and writer threads
    pthread_t reader_threads[4], writer_threads[4];
    int i;

    // Create reader threads
    for (i = 0; i < 4; i++) {
        pthread_create(&reader_threads[i], NULL, reader, readFile);
    }

    // Create writer threads
    for (i = 0; i < 4; i++) {
        pthread_create(&writer_threads[i], NULL, writer, (void*)args);
    }

    // Join reader threads
    for (i = 0; i < 4; i++) {
        pthread_join(reader_threads[i], NULL);
    }

    // Join writer threads
    for (i = 0; i < 4; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    fclose(readFile);
    free(input);
}
