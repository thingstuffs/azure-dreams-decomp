#include "common.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s16 func_800BCB04(s32, s32, s16);
extern s16 D_8006CCD8[];
extern s16 D_8006CCE8[];

/* Checks the adjacent tile's flags and whether its sampled value is below 0x200. */
s32 func_8017506C(s16 tile_x, s16 tile_y, s32 height, s16 direction, s16 *sample_out) {
    u16 tile_flags;
    s16 sample;

    if ((func_8009A350(tile_x, tile_y, direction, &tile_flags) << 16) == 0) {
        return 0;
    }
    if (tile_flags & 0xB700) {
        goto fail;
    }

    sample = func_800BCB04(
        ((tile_x + D_8006CCD8[direction]) << 6) + 0x20 & 0xFFE0,
        ((tile_y + D_8006CCE8[direction]) << 6) + 0x20 & 0xFFE0,
        (s16)(height - 0x20));
    *sample_out = sample;
    if (sample < 0x200) {
        return 1;
    }

fail:
    return 0;
}
