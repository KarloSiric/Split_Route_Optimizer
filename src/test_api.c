/*
* @Author: karlosiric
* @Date:   2025-06-25 14:37:02
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 16:02:57
*/

#include "../include/api/osm_api.h"
#include "../include/core/data_structures.h"

int main(void) {

    printf("Testing the OSM API...\n");

    s_LocationList *list = create_location_list(10);
    if (!list) {
        printf("Failed to create a  location list!\n");
        return -1;
    }

    printf("Created a location list successfully!");

    s_API_Response response;
    const char *url = "https://overpass-api.de/api/interpreter?data=[out:json];node[%22name%22~%22Diocletian%22];out;";
    
    if (fetch_osm_data(url,  &response)) {
        printf("\nFetched data: %zu bytes\n", response.size);

        int count = parse_osm_data(response.data, list);
        printf("Parsed %d locations\n", count);

        if (count > 0) {
            printf("First location %s is at: (%.6f, %.6f)\n",
                list->locations[0].name,
                list->locations[0].lat,
                list->locations[0].lon);
        }

        free_api_response(&response);

    }

    free_location_list(list);
    return 0;
}
