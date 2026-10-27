#include "common.h"

extern void * spawn_killer(s16 flags, s32 kind_id, s32 variant, s32 spawn_value);

/* Exact entry span; owner-unresolved. */
const void *const killer_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_killer
};
