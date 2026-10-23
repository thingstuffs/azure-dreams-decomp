#include "common.h"

extern void damp_and_fade_effect_sprite(void);

/* entry; owner: dungeon/func_80D95000. */
const u32 dreamin_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)damp_and_fade_effect_sprite
};
