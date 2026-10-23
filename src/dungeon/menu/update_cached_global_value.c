#include "common.h"
#include "dungeon/menu.h"

extern s16 floor_generation_state[3];

/* Redraws the floor-generation value when it differs from the cached value, then updates the cache. */
void update_cached_global_value(s32 *cachedValue) {
    if (floor_generation_state[2] != *cachedValue) {
        draw_filler_first_number(floor_generation_state[2], *cachedValue, 2, 0x18C, 0x1B8, 0);
        *cachedValue = floor_generation_state[2];
    }
}
