#include "common.h"
#include "shared/game_work.h"


/* Return whether the coordinates are outside the dungeon bounds. */
s32 func_800A0548(s16 x, s16 y)
{
    MapGrid *bounds = &gameWork.map;

    if (x < 0 || x >= (1 << bounds->shiftX)) {
        return 1;
    }
    if (y < 0 || y >= (1 << bounds->shiftY)) {
        return 1;
    }
    return 0;
}

/* MECHANISM: Frameless leaf; a named DungeonBounds base holds &D_8008333C and
   pulls the page lui to word 0 while reusing a3 for both signed field loads.
   Explicit out-of-range returns reproduce the shared return-one CFG. */
