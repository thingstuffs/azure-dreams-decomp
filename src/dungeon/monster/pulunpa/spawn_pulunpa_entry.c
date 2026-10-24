#include "common.h"

extern void create_actor_grid_object(void);

/* entry; owner: dungeon/func_80CBD000. */
const void *const pulunpa_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    create_actor_grid_object
};
