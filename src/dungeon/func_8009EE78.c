#include "common.h"

extern s32 func_8009A350(s32, s32, s32, s16 *);
extern s32 func_800BCB04(s32, s32, s16);

/* Checks the left tile and tests the height at the current tile center. */
s32 func_800A45D8(s32 x, s32 y, s32 z)
{
    s16 height;
    s32 grid_x;
    s32 grid_y;
    register s32 left_x ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 query_kind;
    s32 tile_x;
    s32 tile_y;
    s32 height_result;
    s32 height_limit;

    grid_x = (u16)x >> 6;
    left_x = grid_x - 1;
    grid_y = (u16)y >> 6;
    query_kind = 0;
    tile_x = grid_x;
    tile_y = grid_y;
    ASM_KEEP(query_kind);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(tile_x);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(tile_y);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(grid_y);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if ((func_8009A350(left_x, grid_y, query_kind, &height) << 16) == 0) {
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
