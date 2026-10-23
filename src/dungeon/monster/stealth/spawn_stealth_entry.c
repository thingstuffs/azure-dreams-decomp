#include "common.h"

extern void spawn_effect_object(void);

/* entry; owner: dungeon/func_80F2D000. */
const u32 stealth_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)spawn_effect_object
};
