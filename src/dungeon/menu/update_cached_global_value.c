#include "common.h"

extern s16 D_80081468[3];
extern void draw_filler_first_number(s32 first_number, s32 second_number, u16 width, s16 y, u16 x, s16 mode);

// Handle changes to D_80081468[2] and update its cached value.
void update_cached_global_value(s32 *cachedValue) {
    if (D_80081468[2] != *cachedValue) {
        draw_filler_first_number(D_80081468[2], *cachedValue, 2, 0x18C, 0x1B8, 0);
        *cachedValue = D_80081468[2];
    }
}
