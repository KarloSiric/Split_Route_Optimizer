/*
* @Author: karlosiric
* @Date:   2025-06-24 11:25:04
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 14:04:44
*/

#include "../../include/api/osm_api.h"
#include <stdlib.h>
#include <string.h>

static size_t write_callback(void *contents, size_t size, size_t nmemb, s_API_Response *response) {
    size_t total = size * nmemb;
    response->data = realloc(response->data, response->size + total);
    if (!response->data) {
        fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
        return -1;
    };

    memcpy(response->data + response->size, contents, total);
    response->size += total;

    return total;
}


int fetch_osm_data(const char *url, s_API_Response *response) {
    response->data = malloc(1);
    response->size = 0;

    CURL *curl = curl_easy_init();
    if (!curl) {
        curl_easy_strerror(CURLE_SSL_ENGINE_INITFAILED);
        return -1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);


    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform failed: %s\n", curl_easy_strerror(res));
        return -1;
    }

    curl_easy_cleanup(curl);
    return (1);
}

s_LocationList *create_location_list(size_t initial_capacity) {
    s_LocationList *list = malloc(sizeof(s_LocationList));
    if (!list) {
        fprintf(stderr, "Memory allocation failure: %s\n", strerror(errno));
        return NULL;
    }

    list->count = 0;
    list->capacity = initial_capacity;

    list->locations = malloc(initial_capacity * sizeof(s_Location));
    if (!list->locations) {
        fprintf(stderr, "Memory allocation failure for array of Locations: %s\n", strerror(errno));
        free(list);
        return NULL;
    }

    return list;
}

int parse_osm_data(const char *data, s_LocationList *location_list) {
    cJSON *json = cJSON_Parse(data);
    if (!json) {
        fprintf(stderr, "Failed to parse JSON\n");
        return -1;
    }

    cJSON *elements = cJSON_GetObjectItem(json, "elements");
    if (!elements) {
        fprintf(stderr, "No 'elements' found in JSON\n");
        cJSON_Delete(json);
        return -1;
    }

   int array_size = cJSON_GetArraySize(elements); 

   for (int i = 0; i < array_size; i++) {
        cJSON *element = cJSON_GetArrayItem(elements, i);

        int id = cJSON_GetObjectItem(element, "id")->valueint;
        double lat = cJSON_GetObjectItem(element, "lat")->valuedouble;
        double lon = cJSON_GetObjectItem(element, "lon")->valuedouble;

        // Get the tags objects 
        cJSON *tags = cJSON_GetObjectItem(element, "tags");
        cJSON *name = cJSON_GetObjectItem(element, "name")->valuestring;
        cJSON *tourism = cJSON_GetObjectItem(element, "tourism")->valuestring;

        // Get a location struct with all this data
        s_Location new_location;
        new_location.id = id;
        new_location.lat = lat;
        new_location.lon = lon;
        strcpy(new_location.name, name);
        strcpy(new_location.tourism_type, tourism);

        // Add this location to our list 
        location_list->locations[location_list->count] = new_location;
        location_list->count++;
   }


















}




