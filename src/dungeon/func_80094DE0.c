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
    s32 x;
    s32 y;
    s32 center_x;
    s32 center_y;
    u16 *x_table;
    u32 dir;
    register s16 saved ASM_REG("$18");
    s16 h;
    s32 odd;

    saved = direction;
    h = height;
    odd = direction & 1;
    if (odd) {
        side = -1;
        x = tile_x;
        center_x = (x << 6) + 0x20;
        x_table = D_800DCEAC;
        y = tile_y;
        center_y = (y << 6) + 0x20;
    loop:
        if (func_8009A350(x, y, (saved + side) & 7, &tile_flags) != 0) {
            dir = ((u16)saved + side) & 7;
            if (func_800BCB04(x_table[dir] + center_x, D_800DCEBC[dir] + center_y, h) > 0x200) {
                goto done;
            }
        }
        side += 2;
        if (side < 2) {
            goto loop;
        }
    done:
        if (side < 2) {
            return 0;
        }
    }
    return 1;
}
