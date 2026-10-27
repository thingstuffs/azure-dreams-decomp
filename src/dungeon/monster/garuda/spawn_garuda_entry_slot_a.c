#include "common.h"

extern void * spawn_garuda_slot_a(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c);

/* entry; owner: dungeon/func_81029000. */
const void *const garuda_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_garuda_slot_a
};
