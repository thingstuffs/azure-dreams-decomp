#include "common.h"

extern void * spawn_mandara_in_slot_d(s16 flags, s16 kind_id, s16 tile_y, s16 spawn_height);

/* entry; owner: dungeon/func_80FC3000. */
const void *const mandara_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_mandara_in_slot_d
};
