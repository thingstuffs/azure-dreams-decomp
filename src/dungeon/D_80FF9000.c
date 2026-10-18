#include "common.h"

extern void allocate_actor_and_initialize_parts(void);

/* entry; owner: dungeon/func_80FF9000. */
const u32 D_80152800[1] __attribute__((aligned(4))) = {
    (u32)allocate_actor_and_initialize_parts
};
