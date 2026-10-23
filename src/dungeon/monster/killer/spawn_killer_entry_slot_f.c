#include "common.h"

extern void spawn_killer_slot_f(void);

/* entry; owner: dungeon/func_80FE1000. */
const u32 killer_slot_f_entry_pointer[1] __attribute__((aligned(4))) = {
    (u32)spawn_killer_slot_f
};
