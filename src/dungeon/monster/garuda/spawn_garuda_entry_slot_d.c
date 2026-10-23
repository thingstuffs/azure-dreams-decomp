#include "common.h"

extern void spawn_garuda_slot_d(void);

/* entry; owner: dungeon/func_81017000. */
const u32 garuda_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)spawn_garuda_slot_d
};
