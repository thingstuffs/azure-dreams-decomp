#include "common.h"

extern void * spawn_mandara_in_slot_c(s32 spawn_flags, s16 tile_x, s16 tile_y, s16 spawn_height);

/* entry; owner: dungeon/func_80FC9000. */
const void *const mandara_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_mandara_in_slot_c
};
