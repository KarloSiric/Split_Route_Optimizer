/*
* @Author: karlosiric
* @Date:   2025-06-25 16:10:46
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 20:26:29
*/

#include "../../include/ui/window.h"
#include "gtk/gtk.h"
#include <string.h>

s_MapApp *create_map_app(s_LocationList *locations) {
    s_MapApp *map = malloc(sizeof(s_MapApp));
    if (!map) {
        fprintf(stderr, "Memory allocation error, not enough space to allocate memory!\n", strerror(errno));
        return NULL;
    }
    // TODO: Implement this just so we can draw this to the MAP using the GTK
    // Hardcoding it for now just to see how it will feel and look!
    map->center_lat = 43.5081162;
    map->center_lon = 16.4395645;

    map->window_height = 900;
    map->window_width = 1440;

    map->locations = locations;
    map->zoom_level = 1.0;
    map->window = NULL;
    map->drawing_area = NULL;

    






}

