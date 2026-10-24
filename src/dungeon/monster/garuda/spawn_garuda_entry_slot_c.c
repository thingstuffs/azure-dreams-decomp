#include "common.h"

extern void spawn_garuda_slot_c(void);

/* entry; owner: dungeon/func_8101D000. */
const void *const garuda_slot_c_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_garuda_slot_c
};
