#include "common.h"

extern void * create_overlay_effect_object(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c);

/* entry; owner-unresolved. */
const void *const weadog_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_overlay_effect_object
};
