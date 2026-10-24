#include "common.h"

extern void spawn_garuda_slot_a(void);

/* entry; owner: dungeon/func_81029000. */
const void *const garuda_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_garuda_slot_a
};
