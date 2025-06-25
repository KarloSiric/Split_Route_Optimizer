#ifndef WINDOW_H
#define WINDOW_H

#include "../../include/api/osm_api.h"
#include <cairo/cairo.h>
#include <stdbool.h>
#include <gtk/gtk.h>
#include <osmgpsmap-1.0/osm-gps-map.h>


typedef struct {
    
    GtkWidget *window;
    GtkWidget *map_widget;

    s_LocationList *locations;

    double center_lat, center_lon;
    double zoom_level;
    int window_width, window_height;

    gboolean is_dragging;
    double last_mouse_x, last_mouse_y;

} s_MapApp;

s_MapApp *create_map_app(s_LocationList *locations);
void create_map_window(s_MapApp *app);
void show_map_window(s_MapApp *app);
void destroy_map_app(s_MapApp *app);

#endif
