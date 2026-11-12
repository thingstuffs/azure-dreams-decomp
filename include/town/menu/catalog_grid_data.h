#ifndef TOWN_MENU_CATALOG_GRID_DATA_H
#define TOWN_MENU_CATALOG_GRID_DATA_H

#include "common.h"

/* Twelve-byte descriptors shared by the catalog grid and detail cells. */
typedef struct CatalogGridPacket {
    u8 f0;
    s8 f1;
    s8 f2;
    s8 f3;
    s16 f4;
    s16 f6;
    s8 f8;
    s8 f9;
    s8 f10;
    s8 f11;
} CatalogGridPacket;

extern CatalogGridPacket catalog_grid_packets[16];

#endif
