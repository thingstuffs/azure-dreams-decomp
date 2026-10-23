#include "common.h"

extern void spawn_killer(void);

/* Exact entry span; owner-unresolved. */
const u32 killer_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer
};
