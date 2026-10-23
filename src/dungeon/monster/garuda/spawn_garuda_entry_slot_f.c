#include "common.h"

extern void spawn_garuda_slot_f(void);

/* entry; owner: dungeon/func_8100B000. */
const u32 garuda_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)spawn_garuda_slot_f
};
