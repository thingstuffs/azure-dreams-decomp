#include "common.h"

extern void * spawn_garuda_slot_f(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);

/* entry; owner: dungeon/func_8100B000. */
const void *const garuda_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_garuda_slot_f
};
