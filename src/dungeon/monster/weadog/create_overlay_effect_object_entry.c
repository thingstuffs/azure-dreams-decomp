#include "common.h"

extern void create_overlay_effect_object(void);

/* entry; owner-unresolved. */
const u32 weadog_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)create_overlay_effect_object
};
