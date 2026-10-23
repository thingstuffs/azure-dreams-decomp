#include "common.h"

extern void create_configured_overlay_actor_third(void);

/* entry; owner: dungeon/func_80F93000. */
const u32 zu_slot_e_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)create_configured_overlay_actor_third
};
