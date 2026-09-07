#include "common.h"

extern s32 func_8009A350(s16, s16, s16, u16 *);
extern s32 func_8009A540(u16, s16, s16, s16);
extern s16 func_800BCB04(s32, s32, s16);
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;

/* Classify movement in a direction by tile flags and destination height. */
s32 func_80018304(s32 input_x, s32 input_y, s32 current_height, s32 direction)
{
    register s32 raw_x ASM_REG("$19");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    register s32 raw_y ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u16 tile_flags;
    s16 tile_x;
    s16 tile_y;
    s16 probe_height;
    s16 dir;
    s16 target_height;
    s32 next_x;
    s32 next_y;

    raw_x = input_x;
    raw_y = input_y;
    probe_height = current_height - 0x20;
    tile_x = raw_x;
    tile_y = raw_y;
    if ((func_8009A540(direction & 0xFFFF, tile_x, tile_y, probe_height) << 16) == 0) {
        goto failure;
    }

    dir = direction;
    if ((func_8009A350(tile_x, tile_y, dir, &tile_flags) << 16) == 0) {
        goto failure;
    }

    next_x = raw_x + ((u16 *)&D_8006CCD8)[dir];
    next_y = raw_y + ((u16 *)&D_8006CCE8)[dir];
    if (tile_flags & 0x8400) {
        goto failure;
    }

    target_height = func_800BCB04(
        (((next_x << 16) >> 10) + 0x20) & 0xFFE0,
        (((next_y << 16) >> 10) + 0x20) & 0xFFE0,
        probe_height);
    if (target_height >= 0x200) {
        goto failure;
    }
    if ((s16)current_height >= target_height) {
        return 2;
    }
    if ((target_height - (s16)current_height) < 0x21) {
        return 1;
    }
failure:
    return 0;
}

