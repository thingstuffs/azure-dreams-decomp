#include "common.h"

extern void spawn_killer_slot_c(void);

/* entry; owner: dungeon/func_80FF3000. */
const u32 D_80158800[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer_slot_c
};
