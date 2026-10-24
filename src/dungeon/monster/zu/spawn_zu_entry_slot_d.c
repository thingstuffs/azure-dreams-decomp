#include "common.h"

extern void spawn_zu_slot_d(void);

/* entry; owner: dungeon/func_80F99000. */
const void *const zu_slot_d_spawn_entry[1] __attribute__((aligned(4))) = {
    spawn_zu_slot_d
};
