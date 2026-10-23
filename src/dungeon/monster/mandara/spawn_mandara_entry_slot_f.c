#include "common.h"

extern void create_actor_with_parts_and_flags(void);

/* entry; owner: dungeon/func_80FB7000. */
const u32 mandara_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)create_actor_with_parts_and_flags
};
