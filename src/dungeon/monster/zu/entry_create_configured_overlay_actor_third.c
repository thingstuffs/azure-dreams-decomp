#include "common.h"

extern void * create_configured_overlay_actor_third(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);

/* entry; owner: dungeon/func_80F93000. */
const void *const zu_slot_e_entry_pointer[1] __attribute__((aligned(4))) = {
    create_configured_overlay_actor_third
};
