#include "common.h"

extern void spawn_killer_slot_d(void);

/* entry; owner: dungeon/func_80FED000. */
const void *const killer_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_d
};
