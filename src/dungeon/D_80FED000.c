#include "common.h"

extern void dungeonAllocateAndInitializeNode(void);

/* entry; owner: dungeon/func_80FED000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)dungeonAllocateAndInitializeNode
};
