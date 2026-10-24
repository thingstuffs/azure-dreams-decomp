#include "common.h"

extern void spawn_killer_slot_c(void);

/* entry; owner: dungeon/func_80FF3000. */
const void *const killer_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_c
};
