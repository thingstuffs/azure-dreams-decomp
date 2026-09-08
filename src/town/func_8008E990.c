#include "common.h"

extern s32 func_8008C0AC();

/* town_map_mod_read_p: convert world coordinates to tiles and compute the map entry address. */
void func_8008C0F0(s16 world_x, s16 world_y) {
    s32 tile_x;
    s32 tile_y;

    tile_x = (s16)world_x;
    if (tile_x < 0) {
        tile_x += 0x3F;
    }
    tile_y = (s16)world_y;
    tile_x >>= 6;
    if (tile_y < 0) {
        tile_y += 0x3F;
    }
    func_8008C0AC(tile_x, tile_y >> 6);
}
