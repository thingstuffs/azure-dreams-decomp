#ifndef ENGINE_TEXTURE_SPRITE_PART_LIST_H
#define ENGINE_TEXTURE_SPRITE_PART_LIST_H

#include "common.h"

/* Leading part-list fields passed to the chain stamper after relocation. */
typedef struct S_80048B8C {
    u8 *list;
    s32 index;
    u8 *listEnd;
} S_80048B8C;

#endif
