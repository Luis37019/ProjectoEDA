#ifndef TRANSPORTES_H
#define TRANSPORTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_GEOCODE_SIZE 100

typedef struct transport {
    int id;
    int type;
    int battery;
    int autonomy;
    char geocode[MAX_GEOCODE_SIZE];
    struct transport* next;
} transport;

extern transport* transportHead;

void cpy_transport(transport* transport1, transport* transport2);
void addTransport();
void updateTransport();
void removeTransport();
void searchByGeocode();

#endif //TRANSPORTES_H