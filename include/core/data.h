#ifndef DATA_H
#define DATA_H 

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    char type[10];
    double lat;
    double lon;
    char name[256];
    char tourism[64];
    char historic[64];
    char website[256];
} s_Location;

typedef struct {
    s_Location *locations;
    int count;
    int size;
} s_LocationList;

typedef struct {
    char *data;
    size_t data_size;
} s_API_Response;


s_LocationList *create_location_list(size_t initial_list_size);
bool parse_json_data(const char *json_data, s_LocationList *location_list_data);
int fetch_osm_data(const char *url, char **json_response);

#endif
