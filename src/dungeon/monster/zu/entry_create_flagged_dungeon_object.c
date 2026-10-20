#include "common.h"

extern void create_flagged_dungeon_object(void);

/* entry; owner: dungeon/func_80FA5000. */
const u32 D_80152800[1] __attribute__((aligned(4))) = {
    (u32)create_flagged_dungeon_object
};
