#ifndef CREATE_FILE_FOR_WORDS_H
#define CREATE_FILE_FOR_WORDS_H

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);
void createFileContentForWords(FILE* file);

#endif