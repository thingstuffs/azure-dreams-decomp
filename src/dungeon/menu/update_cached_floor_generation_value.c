#include "common.h"
#include "shared/dungeon_floor.h"
#include "dungeon/menu.h"
#include "dungeon/actor/entity_spawn_load.h"

/* Redraws the floor-generation value when it differs from the cached value, then updates the cache. */
void update_cached_floor_generation_value(s32 *cachedValue) {
    if (floor_generation_state.floor_number != *cachedValue) {
        draw_hud_number_tall(floor_generation_state.floor_number, *cachedValue, 2, 0x18C, 0x1B8, 0);
        *cachedValue = floor_generation_state.floor_number;
    }
}
