#include "common.h"

extern void create_configured_overlay_actor_alt(void);

/* entry; owner: dungeon/func_80FFF000. */
const u32 D_8014C800[1] __attribute__((aligned(4))) = {
    (u32)create_configured_overlay_actor_alt
};
