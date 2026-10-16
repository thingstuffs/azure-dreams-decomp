#include "common.h"

extern void dungeonAllocateActorAndInitializeParts(void);

/* entry; owner: dungeon/func_80FF9000. */
const u32 D_80152800[1] __attribute__((aligned(4))) = {
    (u32)dungeonAllocateActorAndInitializeParts
};
