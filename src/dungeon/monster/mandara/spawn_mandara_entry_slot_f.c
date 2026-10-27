#include "common.h"

extern void * create_actor_with_parts_and_flags(s32 spawn_flags, s16 pos_x, s16 pos_y, s16 part_a_value);

/* entry; owner: dungeon/func_80FB7000. */
const void *const mandara_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    create_actor_with_parts_and_flags
};
