#include "common.h"

extern void spawn_killer_slot_d(void);

/* entry; owner: dungeon/func_80FED000. */
const u32 killer_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer_slot_d
};
