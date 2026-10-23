#include "common.h"

extern void spawn_tyrant_in_slot_a(void);

/* entry; owner: dungeon/func_8107D000. */
const u32 tyrant_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)spawn_tyrant_in_slot_a
};
