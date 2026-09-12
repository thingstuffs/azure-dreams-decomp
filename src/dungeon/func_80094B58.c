#include "common.h"

extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80083160[];

/* Checks whether the adjacent tile has masked flags or a zero tile value. */
s32 func_8009A2B8(s16 origin_x, s16 origin_y, s32 direction) {
    s32 tile_index;
    s32 tile_y;
    s32 result;
    u8 *dungeon;
    u8 *tile;

    dungeon = D_80083160;
    do {
    } while (0);
    tile_index = origin_x + ((s16 *)D_8006CCD8)[(s16)direction];
    tile_y = origin_y + ((s16 *)D_8006CCE8)[(s16)direction];
    tile_index += tile_y << *(s16 *)(dungeon + 0x1F0);
    tile = *(u8 **)(dungeon + 0x1DC) + tile_index * 6;
    result = *(u16 *)(tile + 4) & 0xF320;
    if (result != 0) {
        result = 1;
        goto done;
    }
    result = *(u16 *)tile;
    if (result != 0) {
        result = 0;
        goto done;
    }
    result = 1;
done:
    return result;
}

/* MECHANISM: Frameless leaf; ASM_KEEP holds D_80083160 at words 0-1.
   Symbolic s16 indexing reproduces the interleaved argument normalization.
   One v0 result lifetime plus an epilogue barrier prevents tail duplication. */
