#include "common.h"

extern void move_and_fade_effect_sprite(void);

/* entry; owner: dungeon/func_80DA1000. */
const void *const dreamin_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    move_and_fade_effect_sprite
};
