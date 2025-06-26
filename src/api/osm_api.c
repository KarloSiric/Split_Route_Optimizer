/*
* @Author: karlosiric
* @Date:   2025-06-26 09:03:28
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-26 09:43:30
*/

#include <cjson/cJSON.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
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

bool parse_json_data(const char *json_data, s_LocationList *location_list_data) {
    
}


