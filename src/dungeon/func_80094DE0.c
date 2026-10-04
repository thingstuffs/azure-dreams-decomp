#include "common.h"

extern s16 func_8009A350(s16, s16, s16, s32 *);
extern s16 func_800BCB04(u16, u16, s16);
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

/* Checks the sides of a diagonal direction for terrain above 0x200. */
s32 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height)
{
    s32 tile_flags;
    s32 side;
    u32 dir;
    s16 saved;
    s16 h;
    s32 x;
    s32 y;

    saved = direction;
    h = height;
    if (direction & 1) {
        x = tile_x;
        y = tile_y;
        for (side = -1; side < 2; side += 2) {
            if (func_8009A350(x, y, (saved + side) & 7, &tile_flags) != 0) {
                dir = ((u16)saved + side) & 7;
                if (func_800BCB04((x << 6) + 0x20 + D_800DCEAC[dir], (y << 6) + 0x20 + D_800DCEBC[dir], h) > 0x200) {
                    break;
                }
            }
        }
        if (side < 2) {
            return 0;
        }
    }
    return 1;
}
