#ifndef TOWN_SHOP_GROUP_INDEX_H
#define TOWN_SHOP_GROUP_INDEX_H

#include "common.h"

/* A value and its zero-based group of ten. Two disjoint instances occur
 * at +0x1c and +0x2c in the storage input body. */
typedef struct TownGroupIndex {
    s32 page;
    s32 index;
    s32 selection;
    s32 value;
} TownGroupIndex;

void get_zero_based_group_index(TownGroupIndex *record);

#endif
