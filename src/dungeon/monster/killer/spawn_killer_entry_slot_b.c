#include "common.h"

extern void * spawn_killer_slot_b(s16 spawn_flags, s32 grid_x, s32 grid_y, s16 part_value);

/* entry; owner: dungeon/func_80FF9000. */
const void *const D_80152800[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_b
};
