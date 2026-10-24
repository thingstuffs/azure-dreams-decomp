#include "common.h"

extern void spawn_killer_slot_a(void);

/* entry; owner: dungeon/func_80FFF000. */
const void *const killer_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_a
};
