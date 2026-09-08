#include "common.h"

typedef struct {
    u8 pad0[0x14];
    s16 field14;
    s16 field16;
} DungeonBounds;

extern DungeonBounds D_8008333C;

/* Return whether the coordinates are outside the dungeon bounds. */
s32 func_800A0548(s16 x, s16 y)
{
    DungeonBounds *bounds = &D_8008333C;

    if (x < 0 || x >= (1 << bounds->field14)) {
        return 1;
    }
    if (y < 0 || y >= (1 << bounds->field16)) {
        return 1;
    }
    return 0;
}

/* MECHANISM: Frameless leaf; a named DungeonBounds base holds &D_8008333C and
   pulls the page lui to word 0 while reusing a3 for both signed field loads.
   Explicit out-of-range returns reproduce the shared return-one CFG. */
