#include "common.h"

extern void * spawn_tyrant_in_slot_a(s16 input0, s16 input1, s16 input2, s16 input3);

/* entry; owner: dungeon/func_8107D000. */
const void *const tyrant_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_tyrant_in_slot_a
};
