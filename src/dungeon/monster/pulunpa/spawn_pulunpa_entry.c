#include "common.h"

extern void spawn_pulunpa_in_slot_g(void);

/* entry; owner: dungeon/func_80CBD000. */
const void *const pulunpa_slot_g_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_pulunpa_in_slot_g
};
