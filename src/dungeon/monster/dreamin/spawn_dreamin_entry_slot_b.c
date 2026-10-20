#include "common.h"

extern void spawn_dreamin_slot_b(void);

/* entry; owner: dungeon/func_80DAD000. */
const u32 D_80152800[1] __attribute__((aligned(4))) = {
    (u32)spawn_dreamin_slot_b
};
