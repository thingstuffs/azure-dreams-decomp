#include "common.h"

extern void * spawn_killer_slot_f(s16 kind_flags, s32 part_value_24, s32 part_value_25, s16 part_value_0a);

/* entry; owner: dungeon/func_80FE1000. */
const void *const killer_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_f
};
