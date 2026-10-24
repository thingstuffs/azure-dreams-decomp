#include "common.h"

extern void spawn_clown_slot_d(void);

/* entry; owner: dungeon/func_80BFD000. */
const void *const clown_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_clown_slot_d
};
