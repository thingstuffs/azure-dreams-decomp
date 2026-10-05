#include "common.h"

extern s32 func_8009A540(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 func_8009FB34(u16, u16);
extern s16 func_800A0818(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);

/* Checks distinct neighboring positions for equal values or a successful fallback check. */
s32 func_8009FE94(s16 x0, s16 y0, s16 check_param, s16 x1, s16 y1) {
    s32 dx;
    s32 dy;
    s32 query_aux;

    dx = __builtin_abs(x1 - x0);
    if (dx >= 2)
        return 0;
    dy = __builtin_abs(y1 - y0);
    if (!(dy >= 2 || dx + dy == 0)) {
        if (func_8009FB34(x0, y0) == func_8009FB34(x1, y1)) {
            return 1;
        }
        if ((s16)func_8009A540((func_800A0818(x0, y0, x1, y1, &query_aux) << 16 >> 25) & 0xFFFF, x0, y0, check_param - 0x20) != 0) {
            return 1;
        }
    }
    return 0;
}
