#include "common.h"

extern void spawn_mandara_in_slot_d(void);

/* entry; owner: dungeon/func_80FC3000. */
const void *const mandara_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_mandara_in_slot_d
};
