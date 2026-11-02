#ifndef DUNGEON_LEVEL_FLOOR_OBJECT_POSITION_ENTRY_H
#define DUNGEON_LEVEL_FLOOR_OBJECT_POSITION_ENTRY_H

#include "common.h"

typedef struct {
    u8 pad0[6];
    union { s8 s; u8 u; } field6;
    union { s8 s; u8 u; } field7;
    union { s32 s; u32 u; } field8;
    s32 fieldC;
    s16 field10;
    u8 pad12[2];
    s16 field14;
    u8 pad16[2];
} D_800E39C8_entry;

#endif
