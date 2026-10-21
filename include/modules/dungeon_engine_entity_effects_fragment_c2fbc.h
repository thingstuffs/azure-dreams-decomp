#ifndef MORE_FRAGMENT_C2FBC_H
#define MORE_FRAGMENT_C2FBC_H
#include "common.h"
typedef struct { u16 flags; u8 pad2[18]; } DungeonItem;
typedef DungeonItem DungeonCell;
typedef struct { u8 pad0[2]; u8 count; u8 pad3[9]; DungeonItem *entries; u8 pad10[4]; } DungeonGroup;
extern DungeonGroup item_category_groups[];
#endif
