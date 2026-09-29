#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"


/* Checks whether the adjacent tile has masked flags or a zero tile value. */
s32 func_8009A2B8(s16 origin_x, s16 origin_y, s32 direction) {
    s32 tile_index;
    s32 tile_y;
    s32 result;
    GameWork *dungeon;
    u8 *tile;

    dungeon = &gameWork;
    do {
    } while (0);
    tile_index = origin_x + ((s16 *)((u8 *)dirStepX))[(s16)direction];
    tile_y = origin_y + ((s16 *)((u8 *)dirStepY))[(s16)direction];
    tile_index += tile_y << dungeon->map.shiftX;
    tile = ((u8 *)dungeon->map.cells) + tile_index * 6;
    result = *(u16 *)(tile + 4) & 0xF320;
    if (result != 0) {
        result = 1;
        return result;
    }
    result = *(u16 *)tile;
    if (result != 0) {
        result = 0;
        return result;
    }
    result = 1;
    return result;
}

/* MECHANISM: Frameless leaf; ASM_KEEP holds D_80083160 at words 0-1.
   Symbolic s16 indexing reproduces the interleaved argument normalization.
   One v0 result lifetime plus an epilogue barrier prevents tail duplication. */
