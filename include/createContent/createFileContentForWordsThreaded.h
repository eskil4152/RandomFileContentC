#ifndef CREATE_FILE_FOR_WORDS_THREADED_H
#define CREATE_FILE_FOR_WORDS_THREADED_H

void* reader(void* arg);
void* writer(void* args);
void createFileContentForWordsThreaded(FILE* file);

#endif