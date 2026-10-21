#include "common.h"

extern s16 floor_generation_state[3];
extern void draw_filler_first_number(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode);

// Handle changes to D_80081468[2] and update its cached value.
void update_cached_global_value(s32 *cachedValue) {
    if (floor_generation_state[2] != *cachedValue) {
        draw_filler_first_number(floor_generation_state[2], *cachedValue, 2, 0x18C, 0x1B8, 0);
        *cachedValue = floor_generation_state[2];
    }
}
