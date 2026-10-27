#include "common.h"

extern void * spawn_dreamin_slot_b(s16 spawn_flags, s16 spawn_x, s16 spawn_y, s16 initial_value);

/* entry; owner: dungeon/func_80DAD000. */
const void *const D_80152800[1] __attribute__((aligned(4))) = {
    spawn_dreamin_slot_b
};
