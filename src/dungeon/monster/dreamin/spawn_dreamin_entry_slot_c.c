#include "common.h"

extern void * damp_effect_motion_and_fade_sprite(s16 init_flags, s16 value_24, s16 value_25, s16 value_0a);

/* entry; owner: dungeon/func_80DA7000. */
const void *const dreamin_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    damp_effect_motion_and_fade_sprite
};
