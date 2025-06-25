#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H 


#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <cjson/cJSON_Utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* Structure for storing data from the OSM API that will be used in the traffic API and be parsed */
typedef struct {
    int id;
    double lat;
    double lon;
    char name[256];
    char name_en[256];         // English name if available
    char tourism_type[64];     // "hotel", "museum", "attraction", etc.
    char historic_type[64];    // "ruins", "monument", etc.
    char website[256];         // URL if available
    char opening_hours[128];   // Hours if available
    char address[256];         // Full address if available
    char stars;                 // Star rating if available
    int has_tourism;           // 1 if tourism field exists
    int has_historic;          // 1 if historic field exists
    int has_website;           // 1 if website field exists
    int has_opening_hours;     // 1 if opening_hours field exists
} s_Location;

typedef struct {
    s_Location *locations;
    size_t count;
    size_t capacity;
} s_LocationList;


#endif
