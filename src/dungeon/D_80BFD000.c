#include "common.h"

extern void create_dungeon_actor(void);

/* entry; owner: dungeon/func_80BFD000. */
const u32 D_8015E800[1] __attribute__((aligned(4))) = {
    (u32)create_dungeon_actor
};
