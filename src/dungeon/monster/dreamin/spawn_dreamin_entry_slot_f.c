#include "common.h"

extern void * damp_and_fade_effect_sprite(s16 init_flags, s16 x, s16 y, s16 initial_value);

/* entry; owner: dungeon/func_80D95000. */
const void *const dreamin_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    damp_and_fade_effect_sprite
};
