#ifndef WINDOW_H
#define WINDOW_H

#include "../../include/api/osm_api.h"
#include <cairo/cairo.h>
#include <stdbool.h>
#include <gtk/gtk.h>


typedef struct {
    
    GtkWidget *window;
    GtkWidget *drawing_area;

    s_LocationList *locations;

    double center_lat, center_lon;
    double zoom_level;
    int window_width, window_height;

    cairo_surface_t *map_surface;

    gboolean is_dragging;
    double last_mouse_x, last_mouse_y;

} s_MapApp;

s_MapApp *create_map_app(s_LocationList *locations);
void create_map_window(s_MapApp *app);
void show_map_window(s_MapApp *app);
void destroy_map_app(s_MapApp *app);

#endif
