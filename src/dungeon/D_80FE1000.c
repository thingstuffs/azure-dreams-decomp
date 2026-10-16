#include "common.h"

extern void createDungeonObjectWithParts(void);

/* entry; owner: dungeon/func_80FE1000. */
const u32 D_8016A800[1] __attribute__((aligned(4))) = {
    (u32)createDungeonObjectWithParts
};
