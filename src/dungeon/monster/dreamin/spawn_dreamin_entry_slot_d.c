#include "common.h"

extern void * move_and_fade_effect_sprite(s16 spawn_flags, s16 grid_x, s16 grid_y, s16 type_id);

/* entry; owner: dungeon/func_80DA1000. */
const void *const dreamin_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    move_and_fade_effect_sprite
};
