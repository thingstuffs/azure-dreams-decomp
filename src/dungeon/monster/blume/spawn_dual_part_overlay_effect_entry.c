#include "common.h"

extern void spawn_dual_part_overlay_effect(void);

/* Exact pointer span; owner-unresolved. */
const u32 blume_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)spawn_dual_part_overlay_effect
};
