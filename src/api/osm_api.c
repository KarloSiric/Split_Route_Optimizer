/*
* @Author: karlosiric
* @Date:   2025-06-26 09:03:28
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-26 10:12:40
*/

#include <cjson/cJSON.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../../include/core/data.h"

s_LocationList *create_location_list(size_t initial_list_size) {

    s_LocationList *location_list = malloc(sizeof(s_LocationList));
    if (!location_list) {
        perror("Error allocating enough memory for location_list array!"); 
        return NULL;
    }

    location_list->locations = malloc(initial_list_size * sizeof(s_Location));

    if (!location_list->locations) {
        perror("Error allocating enough memory for locations!");
        free(location_list);
        return NULL;
    }

    location_list->size = initial_list_size;
    location_list->count = 0;

    return location_list;
}

/* we need our own function that will handle the data 
 * that is being fetched from the https curl request.
*/

/**
 * @brief      Writes a data.
 *
 * @param      buffer  The buffer
 * @param[in]  size    The size of each element in the JSON 
 * @param[in]  nmemb   The nmemb - the number of members inside each element
 * @param      userp   The userp - data taht will be stored our custom data
 *
 * @return     { we return the total amount of bytes the total size that is being returned }
 */

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
    
    s_API_Response *response = (s_API_Response *)userp;
    size_t total_size = size * nmemb;

    response->data = realloc(response->data, response->data_size + total_size + 1); 
    if (!response->data) {
        perror("Memory allocation failed, couldnt reallocate memory!");
        return (0);
    }
    memcpy(response->data + response->data_size, buffer, total_size);
    response->data_size += total_size;
    response->data[response->data_size] = '\0';

    // we need to tell libcurl how many bytes of data we have processed
    return total_size; 
}



int fetch_osm_data(const char *url, char **json_response) {
        
    s_API_Response *response = {0};
    response->data = malloc(NULL);
    response->data_size = 0;

    CURL *handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, url);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);


    






}


