#ifndef TOWN_MENU_CATALOG_FRAME_DATA_H
#define TOWN_MENU_CATALOG_FRAME_DATA_H

#include "common.h"

typedef struct CatalogFrameEntry {
    void *value;
    u16 x;
    u16 y;
} CatalogFrameEntry;

extern CatalogFrameEntry catalog_frame_layout[14];

#endif
