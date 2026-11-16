#include "common.h"

extern void *spawn_ifrit_slot_d(s16, s16, s16, s16);

/* entry; owner: dungeon/func_80A2F000. */
const void *const ifrit_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_ifrit_slot_d
};
