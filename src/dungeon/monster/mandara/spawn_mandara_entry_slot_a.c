#include "common.h"

extern void * spawn_mandara_slot_a(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 heading);

/* entry; owner: dungeon/func_80FD5000. */
const void *const mandara_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_mandara_slot_a
};
