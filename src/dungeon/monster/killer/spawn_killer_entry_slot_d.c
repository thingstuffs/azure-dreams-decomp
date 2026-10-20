#include "common.h"

extern void spawn_killer_slot_d(void);

/* entry; owner: dungeon/func_80FED000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer_slot_d
};
