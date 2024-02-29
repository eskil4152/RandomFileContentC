#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <string.h>
#include "../include/cJSON.h"

void createFile();
void createFileContentForIntegers(FILE* file);
void createFileContentForWords(FILE* file);
int* checkChoice();
int* checkSizeInput();
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

int main(){
    createFile();
}

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
    while (1)
    {
        if (scanf("%d", input) != 1 || (*input != 1 && *input != 2))
        {
            fprintf(stderr, "Invalid input, please enter \n");
            printf("1 for words \n");
            printf("2 for numbers \r\n \r\n \r\n");
            while(getchar() != '\n');
        } else {
            return input;
        }
    }
}

void createFileContentForIntegers(FILE* file){
    int* fileSizeP = checkSizeInput();
    int fileSize = *fileSizeP;
    srand(time(NULL));

    for (int i = 0; i < fileSize; i++)
    {
        fprintf(file, "%d\r\n", rand());
    }
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    char *response_buffer = (char *)userdata;

    // Append received data to response buffer
    memcpy(response_buffer, ptr, total_size);

    // Return the total size of the received data
    return total_size;
}

void createFileContentForWords(FILE* file){
    CURL *curl;
    CURLcode res;
    char response_buffer[4096] = ""; // Adjust size as needed

    // Initialize libcurl
    curl = curl_easy_init();
    if(curl) {
        int* input = checkSizeInput();
        char url[255];

        sprintf(url, "https://random-words5.p.rapidapi.com/getMultipleRandom?count=%d", *input);

        curl_easy_setopt(curl, CURLOPT_URL, url);

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "X-RapidAPI-Key: ff0fc2e49emsh477a9d999010175p12d35ajsnec5da618b16a");
        headers = curl_slist_append(headers, "X-RapidAPI-Host: random-words5.p.rapidapi.com");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the callback function for receiving data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Pass response_buffer as userdata to the callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf("Response:\n%s\n", response_buffer);

        cJSON *json = cJSON_Parse(response_buffer);
        if (json)
        {
            if (file){
                cJSON* word = cJSON_Parse(response_buffer);
                cJSON_ArrayForEach(word, json) {
                        fprintf(file, "%s\n", word->valuestring);
                    }
                    printf("Words written to file.\n");
            } else {
                fprintf(stderr, "Failed to open file for writing.\n");
            }
            cJSON_Delete(json);
        } else {
            fprintf(stderr, "Failed to parse JSON response.\n");
        }
        
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }
    printf("Response: \n%s\n", response_buffer);
}

int* checkSizeInput() {
    int* input = (int*)malloc(sizeof(int));
    if (input == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    printf("Please enter size: \n");
    while (1) {
        if (scanf("%d", input) != 1 || *input <= 1) {
            fprintf(stderr, "Invalid input, please enter a number \n");
            while(getchar() != '\n');
        } else {
            return input;
        }
    }
}
