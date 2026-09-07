#include "common.h"

typedef struct {
    u8 pad0[0x14];
    s16 field14;
    s16 field16;
} DungeonBounds;

extern DungeonBounds D_8008333C;

s32 func_800A0548(s16 arg0, s16 arg1)
{
    DungeonBounds *bounds = &D_8008333C;

    if (arg0 < 0 || arg0 >= (1 << bounds->field14)) {
        return 1;
    }
    if (arg1 < 0 || arg1 >= (1 << bounds->field16)) {
        return 1;
    }
    return 0;
}

/* MECHANISM: Frameless leaf; a named DungeonBounds base holds &D_8008333C and
   pulls the page lui to word 0 while reusing a3 for both signed field loads.
   Explicit out-of-range returns reproduce the shared return-one CFG. */
