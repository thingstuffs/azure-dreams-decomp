#include "common.h"

extern void spawn_killer_slot_a(void);

/* entry; owner: dungeon/func_80FFF000. */
const u32 D_8014C800[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer_slot_a
};
