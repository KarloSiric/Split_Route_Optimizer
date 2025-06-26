#ifndef DATA_H
#define DATA_H 

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
    int capacity;
} s_LocationList;




#endif
