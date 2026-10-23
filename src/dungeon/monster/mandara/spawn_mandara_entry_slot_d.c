#include "common.h"

extern void spawn_mandara_in_slot_d(void);

/* entry; owner: dungeon/func_80FC3000. */
const u32 mandara_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)spawn_mandara_in_slot_d
};
