#include "common.h"

extern void move_expand_and_fade_effect_sprite(void);

/* entry; owner: dungeon/func_80DB3000. */
const void *const dreamin_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    move_expand_and_fade_effect_sprite
};
