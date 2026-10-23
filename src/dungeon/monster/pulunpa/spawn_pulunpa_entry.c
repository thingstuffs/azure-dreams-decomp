#include "common.h"

extern void create_actor_grid_object(void);

/* entry; owner: dungeon/func_80CBD000. */
const u32 pulunpa_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)create_actor_grid_object
};
