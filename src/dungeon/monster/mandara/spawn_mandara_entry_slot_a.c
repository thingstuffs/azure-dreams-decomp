#include "common.h"

extern void spawn_mandara_slot_a(void);

/* entry; owner: dungeon/func_80FD5000. */
const void *const mandara_slot_a_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_mandara_slot_a
};
