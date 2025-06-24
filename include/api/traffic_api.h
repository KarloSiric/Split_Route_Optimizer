/**
 * @file traffic_api.h
 * @brief Header file for Traffic API
 * @author Karlo Siric
 * @version 1.0.0
 * @date 2025-06-12
 * 
 * @description
 * This file contains the declarations for the Traffic API, which provides
 * functions to interact with traffic data services. It includes functions for
 * retrieving traffic information, managing traffic data, and handling API requests.
 * 
 * @license MIT License
 * 
 * Copyright (c) 2025 Karlo Širić
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */



#ifndef TRAFFIC_API_H
#define TRAFFIC_API_H 

#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <cjson/cJSON_Utils.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    char *data;
    size_t size;
} s_API_Response;

/* Structure for storing data from the OSM API that will be used in the traffic API and be parsed */
typedef struct {
    int id;
    double lat;
    double lon;
    char name[256];
    char tourism_type[64];
} s_Location;

typedef struct {
    s_Location *locations;
    size_t count;
    size_t capacity;
} s_LocationList;

int fetch_osm_data(const char *url, s_API_Response *response);
void free_api_response(s_API_Response *response);

#endif
