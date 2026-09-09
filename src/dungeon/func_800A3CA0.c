#include "common.h"

extern u8 D_800DD8E7[9];
extern u8 *D_800E3D7C;

/* Maps special tile codes to mode-dependent values, otherwise returning the tile index. */

s32 func_800A9400(s32 tile_index)
{
    s16 index;
    u8 *tile;
    s32 tile_code;

    index = tile_index;
    tile = D_800DD8E7 + (s16)tile_index;
    tile_code = *tile;

    if (*(*(u8 **)(D_800E3D7C + 0x4C) + 1) != 0) {
        if (tile_code == 0x32) {
            return 7;
        }
        if (tile_code == 0x39) {
            return 8;
        }
        if (tile_code == 0x40) {
            return 9;
        }
    } else {
        if (tile_code == 0x32) {
            return 1;
        }
        if (tile_code == 0x39) {
            return 2;
        }
        if (tile_code == 0x40) {
            return 3;
        }
    }

    return index;
}
