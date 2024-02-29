#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include "../include/tools/cJSON.h"
#include "../include/createContent/createFileContentForWords.h"
#include "../include/inputValidators/checkSizeInput.h"

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

void createFileContentForWords(FILE* file){
    CURL *curl;
    CURLcode res;
    char response_buffer[4096] = "";

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
                    printf("Words successfully written to file.\n");
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
}

size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    char *response_buffer = (char *)userdata;

    // Append received data to response buffer
    memcpy(response_buffer, ptr, total_size);

    // Return the total size of the received data
    return total_size;
}
