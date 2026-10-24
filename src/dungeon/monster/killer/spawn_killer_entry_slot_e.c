#include "common.h"

extern void spawn_killer_slot_e(void);

/* entry; owner: dungeon/func_80FE7000. */
const void *const killer_slot_e_entry_pointer[1] __attribute__((aligned(4))) = {
    spawn_killer_slot_e
};
