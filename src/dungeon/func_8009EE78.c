#include "common.h"

extern s32 getOffsetMapCellValueAndFlags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 func_800BCB04(s32, s32, s16);

/* Checks the left tile and tests the height at the current tile center. */
s32 dungeonCheckLeftTileAndCenterHeight(s32 x, s32 y, s32 z)
{
    s16 height;
    s32 grid_x;
    s32 grid_y;
    u16 tile_x;
    u16 tile_y;
    s32 height_result;
    s32 height_limit;

    grid_x = (u16)x >> 6;
    grid_y = (u16)y >> 6;
    tile_x = grid_x;
    tile_y = grid_y;
    if ((getOffsetMapCellValueAndFlags(grid_x - 1, grid_y, 0, &height) << 16) == 0) {
        return 0;
    }
    if (height & 0x8000) {
        return 1;
    }

    height_result = func_800BCB04((tile_x << 6) | 0x20,
                                  (tile_y << 6) | 0x20,
                                  (s16)(z - 0x20));
    height = height_result;
    height_result <<= 16;
    height_limit = 0x02000000;

    return height_limit < height_result;
}
