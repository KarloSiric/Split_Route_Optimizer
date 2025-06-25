/*
* @Author: karlosiric
* @Date:   2025-06-24 11:25:04
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 14:27:08
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
        if (!tags) continue;


        cJSON *name = cJSON_GetObjectItem(tags, "name");
        cJSON *name_en = cJSON_GetObjectItem(tags, "name:en");
        cJSON *address_city = cJSON_GetObjectItem(tags, "addr:city");
        cJSON *address_housenumber = cJSON_GetObjectItem(tags, "addr:housenumber");
        cJSON *address_postcode = cJSON_GetObjectItem(tags, "addr:postcode");
        cJSON *address_street = cJSON_GetObjectItem(tags, "addr:street");
        cJSON *stars = cJSON_GetObjectItem(tags, "stars");
        cJSON *tourism_item = cJSON_GetObjectItem(tags, "tourism");
        cJSON *historic = cJSON_GetObjectItem(tags, "historic");
        cJSON* website = cJSON_GetObjectItem(tags, "website");
        cJSON* opening_hours = cJSON_GetObjectItem(tags, "opening_hours");




        // Get a location struct with all this data
        s_Location new_location = {0};
        new_location.id = id;
        new_location.lat = lat;
        new_location.lon = lon;


        // Now we check all the tags objects that our structure can hold

        if (tourism_item) {
            strcpy(new_location.tourism_type, tourism_item->valuestring);
            new_location.has_tourism = 1;
        } else {
            strcpy(new_location.tourism_type, "");
            new_location.has_tourism = 0;
        }

        if (historic) {
            strcpy(new_location.historic_type, historic->valuestring);
            new_location.has_historic = 1;
        } else {
            strcpy(new_location.historic_type, "");
            new_location.has_historic = 0;
        }

        if (name) {
            strcpy(new_location.name, name->valuestring);
        } else {
            strcpy(new_location.name, "");
        }

        if (name_en) {
            strcpy(new_location.name_en, name_en->valuestring);
        } else {
            strcpy(new_location.name_en, "");
        }

        // Website
        if (website) {
            strcpy(new_location.website, website->valuestring);
            new_location.has_website = 1;
        } else {
            strcpy(new_location.website, "");
            new_location.has_website = 0;
        }
        
        // Opening hours
        if (opening_hours) {
            strcpy(new_location.opening_hours, opening_hours->valuestring);
            new_location.has_opening_hours = 1;
        } else {
            strcpy(new_location.opening_hours, "");
            new_location.has_opening_hours = 0;
        }
        
        // Stars
        if (stars) {
            new_location.stars = atoi(stars->valuestring);  // Convert string to int
        } else {
            new_location.stars = 0;
        }
        
        // Build full address from parts
        char full_address[256] = "";
        if (address_housenumber) {
            strcat(full_address, address_housenumber->valuestring);
            strcat(full_address, " ");
        }
        if (address_street) {
            strcat(full_address, address_street->valuestring);
            strcat(full_address, ", ");
        }
        if (address_city) {
            strcat(full_address, address_city->valuestring);
            strcat(full_address, " ");
        }
        if (address_postcode) {
            strcat(full_address, address_postcode->valuestring);
        }
        strcpy(new_location.address, full_address);
        
        // Add location to list
        location_list->locations[location_list->count] = new_location;
        location_list->count++;
        
   }

   cJSON_Delete(json);
   return location_list->count;


}

