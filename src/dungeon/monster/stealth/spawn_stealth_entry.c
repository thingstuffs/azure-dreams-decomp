#include "common.h"

extern void *spawn_stealth_slot_a(s16, s16, s16, s16);

/* entry; owner: dungeon/func_80F2D000. */
const void *const stealth_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_stealth_slot_a
};
