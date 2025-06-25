/*
* @Author: karlosiric
* @Date:   2025-06-25 16:10:46
* @Last Modified by:   karlosiric
* @Last Modified time: 2025-06-25 21:09:17
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
    map->map_surface = NULL;
    map->is_dragging = false;

    map->last_mouse_x = 0.0;
    map->last_mouse_y = 0.0;

    return map;
}

void create_map_window(s_MapApp *app) {
    app->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(app->window), "Interactive Map");

    gtk_window_set_default_size(GTK_WINDOW(app->window), app->window_width, app->window_height);

    // TODO: Now we create a drawing area where we will draw things   
    app->drawing_area = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(app->window), app->drawing_area);

    // TODO: Now we have the windows setup and now we need to show these widgets
    gtk_widget_show_all(app->window);
    


}



