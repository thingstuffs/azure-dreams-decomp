#ifndef TOWN_MENU_CATALOG_DETAIL_DATA_H
#define TOWN_MENU_CATALOG_DETAIL_DATA_H

#include "common.h"

typedef struct CatalogDetailImageList {
    void **images;
    u8 count;
    u8 pad[3];
} CatalogDetailImageList;

extern CatalogDetailImageList catalog_detail_images[];

#endif
