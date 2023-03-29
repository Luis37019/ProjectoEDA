#ifndef TRANSPORTES_H
#define TRANSPORTES_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRANSPORTS_FILE "transports.txt"
#define MAX_GEOCODE_SIZE 100

typedef struct transports_data {
    int id;
    int type;
    int battery;
    int autonomy;
    char geocode[MAX_GEOCODE_SIZE];
} transports_data;

void add_transport(transports_data transport);

void remove_transport(int id);

void edit_transport(int id, transports_data new_transport);

#endif // TRANSPORTES_H