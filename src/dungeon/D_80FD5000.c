#include "common.h"

extern void create_monster_actor_and_palette(void);

/* entry; owner: dungeon/func_80FD5000. */
const u32 D_8014C800[1] __attribute__((aligned(4))) = {
    (u32)create_monster_actor_and_palette
};
