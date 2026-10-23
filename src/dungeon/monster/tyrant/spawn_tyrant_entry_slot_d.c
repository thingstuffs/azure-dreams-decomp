#include "common.h"

extern void create_flagged_actor_object_2(void);

/* entry; owner: dungeon/func_8106B000. */
const u32 tyrant_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    (u32)create_flagged_actor_object_2
};
