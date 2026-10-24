#include "common.h"

extern void spawn_tyrant_in_slot_a(void);

/* entry; owner: dungeon/func_8107D000. */
const void *const tyrant_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_tyrant_in_slot_a
};
