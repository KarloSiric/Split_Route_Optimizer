/*
* @Author: karlosiric
* @Date:   2025-06-25 21:45:35
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 22:28:44
*/

#include "../include/ui/window.h"
#include "gtk/gtk.h"
#include <string.h>

int main(int argc, char *argv[])
{
    s_MapApp *app;
    gtk_init(&argc, &argv);
    s_LocationList *list = create_location_list(10);

    if (!list) {
        fprintf(stderr, "Error memory allocation failure!", strerror(errno));
        return (0);
    }

    s_API_Response response;
    const char *url = "https://overpass-api.de/api/interpreter?data=[out:json];node[%22name%22~%22Diocletian%22];out;";

    if (fetch_osm_data(url, &response)) {
        int count = parse_osm_data(response.data, list);
    } else {
        fprintf(stderr, "Couldnt fetch correct data at all!", strerror(errno));
        return (0);
    }

    app = create_map_app(list);
    create_map_window(app);

    gtk_main();

    // TODO: Implementing the cleanup that will run after the user closes the main window
    free_api_response(&response);
    destroy_map_app(app);
    free_location_list(list);

    return (0);
}
