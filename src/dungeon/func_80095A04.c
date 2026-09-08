#include "common.h"

typedef struct {
    s32 unk0[2];
    s32 unk8;
    s32 unkC[2];
    s32 unk14;
} Arg1;

typedef struct {
    u8 pad0[0x24];
    u8 x;
    u8 y;
} Arg2;

extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
s32 func_8009A350();
s16 func_800BCB04();

/* Checks the neighboring tile in the encoded direction for blocking flags and height. */
s32 func_8009B164(u32 direction_bits, Arg1 *state_in, Arg2 *position_in) {
    u16 tile_flags;
    Arg1 *state;
    Arg2 *position;
    s32 direction;
    s32 next_x;
    s32 next_y;

    state = state_in;
    position = position_in;
    direction = (direction_bits >> 9) & 7;
    if ((func_8009A350(position->x, position->y, direction, &tile_flags) << 0x10) == 0) {
        goto return_one;
    }
    if (tile_flags & 0x8000) {
        goto return_zero;
    }
    next_x = position->x + D_8006CCD8[direction];
    next_y = position->y + D_8006CCE8[direction];
    if (func_800BCB04((((s32) (next_x << 0x10) >> 0xA) | 0x20) & 0xFFE0, (((s32) (next_y << 0x10) >> 0xA) | 0x20) & 0xFFE0, (s32) (state->unk8 + (state->unk14 * 2)) >> 0x10) >= 0x200) {
        goto return_zero;
    }
return_one:
    return 1;
return_zero:
    return 0;
}
