#include "common.h"

extern void create_configured_overlay_actor(void);

/* entry; owner: dungeon/func_8101D000. */
const u32 D_80158800[1] __attribute__((aligned(4))) = {
    (u32)create_configured_overlay_actor
};
